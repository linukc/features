- Jetson Nano https://www.dlology.com/blog/how-to-run-keras-model-on-jetson-nano-in-nvidia-docker-container/

- Dockerfile example https://github.com/pytorch/pytorch/blob/master/docker/pytorch/Dockerfile

- Для nvidia нужно провести на хост предустановку (https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/install-guide.html#docker)

- Cache for multi-stage build (https://pythonspeed.com/articles/faster-multi-stage-builds/)

- Saving pip install from previous stage (https://pythonspeed.com/articles/multi-stage-docker-python/)

- Jetson + dont forget set nvidia as druntime in daemon.json after installing nvidia container runtime (https://dev.to/caelinsutch/running-docker-containers-for-the-nvidia-jetson-nano-5a06)

- Hardware Acceleration http://wiki.ros.org/docker/Tutorials/Hardware%20Acceleration

Commands:

delete all <none> image **docker rmi $(docker images -f "dangling=true" -q)**
  
delete all containers **docker rm $(docker ps -a -q)**

delete all images **docker rmi $(docker images -a -q)**

[none:none images](https://habr.com/ru/post/304134/)

**docker images prune**

useful for attaching datasets to docker container **docker run -ti -v ~/Downloads/datasets:/datasets --rm --runtime nvidia <image>**

You can accelerate the build of the docker image with --build-arg NUM_THREADS=number of parallel builds

 - [User inside docker container](https://almat.su/docker-zapusk-protsessa-iz-pod-tekushhego-polzovatelya/) ([about users in Linux](https://sonikelf.ru/polzovatel-root-i-drugie-polzovateli-gruppy-v-linux/)). Example - work_SOLO, my dotmask repo

