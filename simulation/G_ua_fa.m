function [output,R,pos] = G_ua_fa(theta, pos)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
theta_1 = theta(1);

R = [1 0 0;
       0 cos(theta_1) -sin(theta_1);
       0 sin(theta_1) cos(theta_1)];
% rotate around the x axis

output = [R pos; 
          zeros(1,3) 1];
   
end

