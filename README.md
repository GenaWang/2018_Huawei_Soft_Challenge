## Ranking
2018 Huawei Software Elite Challenge Preliminary Code - Northwest Division 39.
***
## Usage of this program
on the ubuntu 14.04 int the "ecs" floder: sh build.sh
***
## Function of this program
This project mainly predicts the number of virtual machine applications for a period of time in the future according to the history of virtual machine (VM) applications. 
According to the predicted number of virtual machines, they are reasonably placed on the physical server, making better use of the server's resources (memory and CPU).
***
## Algorithm of this code
Firstly, we use the BP neural network and the linear weighted method to forecast, and give the weights to the above two prediction methods.
***
Secondly,we use a greedy algorithm to place the virtual machine on the server.
