### Credits
https://github.com/heptio/example-lamp

### Istruction to deploy:

In order..

```console
kubectl apply -f persistantVolume.yaml
kubectl apply -f persistantVolumeClaim.yaml
kubectl apply -f secrets.yaml
kubectl apply -f php.yaml
kubectl apply -f ingress.yaml
```
Last step can take a couple of minutes.


Note, for test runs on minikube run first:
```console
minikube addons enable ingress
```
