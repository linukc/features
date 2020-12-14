- Jetson Nano https://www.dlology.com/blog/how-to-run-keras-model-on-jetson-nano-in-nvidia-docker-container/

- Dockerfile example https://github.com/pytorch/pytorch/blob/master/docker/pytorch/Dockerfile

Commands:

delete all <none> image **docker rmi $(docker images -f "dangling=true" -q)**
  
delete all containers **docker rm $(docker ps -a -q)**

delete all images **docker rmi $(docker images -a -q)**

