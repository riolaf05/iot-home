#!/bin/bash

# By Sharon Campbell, Ken Simon, and Joe Beda for Heptio

# if any commands in this script fail, the whole script returns nonzero
# which means the Job mysql-data-loader-with-timeout
# will keep running this script until it completes successfully
set -o errexit
set -o pipefail
set -o nounset

# Ensure required environment variables are set up
# These env variables are set by Kubernetes in the data-loader-job.yaml file
# and in the php.yaml file, so make sure those two Kubernetes files stay in sync
# The secrets themselves are stored in secrets.yaml
test -n "${MYSQL_USER}"
test -n "${MYSQL_PASSWORD}"
test -n "${MYSQL_HOST}"

# Add MySQL creds to the mysql-credentials.cnf file
# This allows for warning-free mysql command line use
credentialsFile=/mysql-credentials.cnf
cat >$credentialsFile <<EOF
[client]
user=${MYSQL_USER}
password=${MYSQL_PASSWORD}
host=${MYSQL_HOST}
EOF

# initialize DBCOUNT
DBCOUNT=0

# Download the SQL files for the Sakila test database
curl -O https://downloads.mysql.com/docs/sakila-db.tar.gz
  
# unpack
tar -xzf sakila-db.tar.gz

# Does data exist?
function check_data() {
  # assign output of this MySQL query to DBCOUNT
  # output is just 997, no warnings
  # change this query if you want to use this script with different data
  # it should check for something expected in the finished database
  DBCOUNT=$(mysql --defaults-extra-file=$credentialsFile -NBD sakila -e 'select count(*) from nicer_but_slower_film_list;' || echo 0)

  # if the answer to my query is not 997, return 1 (unsuccessful)
  # change this if statement
  # if you want to use this script with a different query or different data
  # this will return 1 on the first try because we haven't imported the data yet
  if [[ "${DBCOUNT}" == "997" ]]; then
    return 0
  else
    return 1
  fi
}

# until the check_data() function returns 0
# which only happens if our MySQL query returns 997
# try to initialize the database
# this will happen at least once because we haven't imported the data yet
until check_data; do
  #make sure we're using the mysql-credentials.cnf for connections
  credentialsFile=/mysql-credentials.cnf

  #restore the database schema and data
  mysql --defaults-extra-file=$credentialsFile < sakila-db/sakila-schema.sql
  mysql --defaults-extra-file=$credentialsFile < sakila-db/sakila-data.sql
done
