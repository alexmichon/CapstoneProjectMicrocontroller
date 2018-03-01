clc
clear all

n = 6; % number of state
q = 0.1;
r=0.1;    %std of measurement
Q = q^2*eye(n);
R = r^2;
fre= 50;  %frequency 50Hz
T = 1/fre;

s=zeros(n,1);    % initial state
x=s+q*randn(n,1); %initial state          % initial state with noise
P = eye(n);                               % initial state covraiance
N=20;                                     % total dynamic steps
xV = zeros(n,N);          %estmate        % allocate memory
sV = zeros(n,N);          %actual
% zV = zeros(1,N);

U = [1 T T^2/2;
     0 1 T;
     0 0 1];
h=@(x)blkdiag(U,U)*x; 
for k=1:N
  z = h(s) + r*randn(n,1);                     % measurments
  sV(:,k)= s;                             % save actual state
%   zV(k)  = z;                             % save measurment
  [x, P] = ukf(f,x,P,h,z,Q,R);            % ekf 
  xV(:,k) = x;                            % save estimate
  s = f(s) + q*randn(3,1);                % update process 
end
for k=1:3                                 % plot results
  subplot(3,1,k)
  plot(1:N, sV(k,:), '-', 1:N, xV(k,:), '--')
end








