function output = f(X)

% X = sym('x',[9 1]);
% % X is 21-by-1 vector
% % 
% output = zeros(size(X,1),1);
% 
t1 = X(1); 
dt1 = X(2); 
ddt1 = X(3);
% assume(t1,'real');assume(dt1,'real');assume(ddt1,'real');
t2 = X(4); dt2 = X(5); ddt2 = X(6);
% assume(t2,'real');assume(dt2,'real');assume(ddt2,'real');

% t3 = X(7); dt3 = X(8); ddt3 = X(9); 
% t4 = X(10); dt4 = X(11); ddt4 = X(12); 
% t5 = X(13); dt5 = X(14); ddt5 = X(15); 
% t6 = X(16); dt6 = X(17); ddt6 = X(18);
% 
% t7 = X(19); dt7 = X(20); ddt7 = X(21);

%% IMU1

Lx = 1; Ly = 1; Lz = 1;
% Lx2 = 0; Ly2 = 1; Lz2 = 1;
% Lx3 = 0; Ly3 = 1; Lz3 = 1;

V_1 = [0 0 0 0 0 1]'.*dt1;

V_12 = [0 0 0 0 1 0]'.*dt2;
R_1 = Rz(t1);
p_b1 = [Lx Ly Lz]';
V_2 = Ad_1(R_1, p_b1)*V_12 + V_1;

% V_23 = [0 0 0 1 0 0]'.*dt3;
% R_b2 = R_b1*Ry(t3);
% p_b2 = [Lx Ly Lz]';
% V_b3 = V_b2 + Ad(R_b2, p_b2)*V_23;

IMU1 = diff(V_2,t1)*dt1 + diff(V_2,t2)*dt2 + diff(V_2,dt1)*ddt1 + diff(V_2,dt2)*ddt2; 
IMU1_acc = IMU1(1:3,:);
IMU1_w = V_2(4:end,:);

output = simplify([IMU1_acc;
          IMU1_w]);
end
