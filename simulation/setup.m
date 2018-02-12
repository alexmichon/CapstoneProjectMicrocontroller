clc
clear all

syms t1 dt1 t2 dt2 t3 dt3 ddt1 ddt2 ddt3
syms t4 dt4 t5 dt5 t6 dt6 ddt4 ddt5 ddt6
syms t7 dt7 ddt7

Lx = 1; Ly = 1; Lz = 1;
Lx2 = 0; Ly2 = 1; Lz2 = 1;
Lx3 = 0; Ly3 = 1; Lz3 = 1;

%% IMU1

V_b1 = [0 0 0 0 0 1]'.*dt1;

V_12 = [0 0 0 0 1 0]'.*dt2;
R_b1 = Rz(t1);
p_b1 = [Lx Ly Lz]';
V_b2 = V_b1 + Ad(R_b1, p_b1)*V_12;

V_23 = [0 0 0 1 0 0]'.*dt3;
R_b2 = R_b1*Ry(t3);
p_b2 = [Lx Ly Lz]';
V_b3 = V_b2 + Ad(R_b2, p_b2)*V_23;
IMU1 = diff(V_b3,t1)*dt1 + diff(V_b3,t2)*dt2 + diff(V_b3,t3)*dt3 + diff(V_b3,dt1)*ddt1 + diff(V_b3,dt2)*ddt2 + diff(V_b3,dt3)*ddt3; 



%% IMU2

V_34 = [0 0 0 0 0 1]'.*dt4;
R_b3 = R_b2*Rz(t4);
p_b3 = [Lx2 Ly2 Lz2]';
V_b4 = V_b3 + Ad(R_b3, p_b3)*V_34;

V_45 = [0 0 0 0 1 0]'.*dt5;
R_b4 = R_b3*Ry(t4);
p_b4 = [Lx2 Ly2 Lz2]';
V_b5 = V_b4 + Ad(R_b4,p_b4)*V_45;

V_56 = [0 0 0 1 0 0]'.*dt6;
R_b5 = R_b3*Ry(t4);
p_b5 = [Lx2 Ly2 Lz2]';
V_b6 = V_b5 + Ad(R_b5,p_b5)*V_56;

IMU2 = diff(V_b6,t1)*dt1 + diff(V_b6,t2)*dt2 + diff(V_b6,t3)*dt3 + diff(V_b6,dt1)*ddt1 + diff(V_b6,dt2)*ddt2 + diff(V_b6,dt3)*ddt3 + ... 
       diff(V_b6,t4)*dt4 + diff(V_b6,t5)*dt5 + diff(V_b6,t6)*dt6 + diff(V_b6,dt4)*ddt4 + diff(V_b6,dt5)*ddt5 + diff(V_b6,dt6)*ddt6; 

%% IMU3

V_67 = [0 0 0 1 0 0]'.*dt7;
R_b6 = R_b5*Rx(t7);
p_b6 = [Lx3 Ly3 Lz3]';
V_b7 = simplify(V_b6 + Ad(R_b6,p_b6)*V_67);



%% Simulation in discrete time
N = 100;
f = 50;  %frequency 50Hz
T = 1/f;

X = zeros(7*3,N);
U = [1 T T^2/2;
     0 1 T;
     0 0 1];
W = blkdiag(U,U,U,U,U,U,U);
Noise = [T^3/6;T^2/2;T];
Noise = repmat(Noise,7,1).*randn(21,1);

for i = 1:1:N+1
    if i < 50
        X(:,i+1) = W*X(:,i) + Noise;      
    else 
        X(:,i+1) = W*X(:,i);
    end
end
%%
figure
ss = 1:1:size(X,2)
for i = 1:1:size(X,1)
    plot(ss,X(i,:));
    hold on   
end
legend('theta_1','theta_1 dot','theta_1 dot dot','theta2','...')
xlabel('Time');
ylabel('state Error');
title('Estimated state');


















   