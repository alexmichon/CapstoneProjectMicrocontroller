function [output,R,pos] = G_world_torso(theta, pos)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
theta_1 = theta(1);
theta_2 = theta(2);
theta_3 = theta(3);
R_x = [1 0 0;
       0 cos(theta_1) -sin(theta_1);
       0 sin(theta_1) cos(theta_1)];
R_y = [cos(theta_2) 0 sin(theta_2);
       0 1 0;
       -sin(theta_2) 0 cos(theta_2)];
   
R_z = [cos(theta_3) -sin(theta_3) 0;
       sin(theta_3)  cos(theta_3) 0;
       0 0 1];
R = R_x*R_y*R_z; 

output = [R pos; 
          zeros(1,3) 1];
   
end

