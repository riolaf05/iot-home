VERSION=$1
docker build -t rio05docker/raspberry_container_generic:camera${VERSION} .
docker push rio05docker/raspberry_container_generic:camera${VERSION}