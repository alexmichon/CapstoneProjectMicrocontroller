close all;
clear;

%% Constants
global g RAD2DEG;
g = 9.81;
RAD2DEG = 180/pi;

%% Time
global dt;
fs = 50;
dt = 1/fs;

t0 = 0;
tf = 8;
t  = t0:dt:tf;

tN = size(t,2);

fs = 1 / dt;
f_torso = 0.2;
f_arm = 0.1;



%% Parameters

% Torso -> IMU 0
global theta_T0_x theta_T0_y theta_T0_z;
global p_T0_x p_T0_y p_T0_z;

% Torso -> Shoulder
global theta_TS_x theta_TS_y theta_TS_z;
global p_TS_x p_TS_y p_TS_z;

% Shoulder -> IMU 1
global theta_S1_x theta_S1_y theta_S1_z; 
global p_S1_x p_S1_y p_S1_z;

% Shoulder -> Elbow
global theta_SE_x theta_SE_y theta_SE_z;
global p_SE_x p_SE_y p_SE_z;

% Elbow -> Forearm
global theta_EF_x theta_EF_y theta_EF_z;
global p_EF_x p_EF_y p_EF_z;

% Forearm -> IMU 2
global theta_F2_x theta_F2_y theta_F2_z;
global p_F2_x p_F2_y p_F2_z;


%% Real parameters
% Values
theta_T0_x_a = 0;
theta_T0_y_a = 0;
theta_T0_z_a = 0;
p_T0_x_a = 0;
p_T0_y_a = 0;
p_T0_z_a = 0;

theta_TS_x_a = 0;
theta_TS_y_a = 0;
theta_TS_z_a = 0;
p_TS_x_a = 0;
p_TS_y_a = 0;
p_TS_z_a = 0;

theta_S1_x_a = 0;
theta_S1_y_a = 0;
theta_S1_z_a = 0;
p_S1_x_a = 0;
p_S1_y_a = 0;
p_S1_z_a = 0;

theta_SE_x_a = 0;
theta_SE_y_a = 0;
theta_SE_z_a = 0;
p_SE_x_a = 0;
p_SE_y_a = 0;
p_SE_z_a = 0;

theta_EF_x_a = 0;
theta_EF_y_a = 0;
theta_EF_z_a = 0;
p_EF_x_a = 0;
p_EF_y_a = 0;
p_EF_z_a = 0;

theta_F2_x_a = 0;
theta_F2_y_a = 0;
theta_F2_z_a = 0;
p_F2_x_a = 0;
p_F2_y_a = 0;
p_F2_z_a = 0;

% Setting
theta_T0_x = theta_T0_x_a;
theta_T0_y = theta_T0_y_a;
theta_T0_z = theta_T0_z_a;
p_T0_x = p_T0_x_a;
p_T0_y = p_T0_y_a;
p_T0_z = p_T0_z_a;

theta_TS_x = theta_TS_x_a;
theta_TS_y = theta_TS_y_a;
theta_TS_z = theta_TS_z_a;
p_TS_x = p_TS_x_a;
p_TS_y = p_TS_y_a;
p_TS_z = p_TS_z_a;

theta_S1_x = theta_S1_x_a;
theta_S1_y = theta_S1_y_a;
theta_S1_z = theta_S1_z_a;
p_S1_x = p_S1_x_a;
p_S1_y = p_S1_y_a;
p_S1_z = p_S1_z_a;

theta_SE_x = theta_SE_x_a;
theta_SE_y = theta_SE_y_a;
theta_SE_z = theta_SE_z_a;
p_SE_x = p_SE_x_a;
p_SE_y = p_SE_y_a;
p_SE_z = p_SE_z_a;

theta_EF_x = theta_EF_x_a;
theta_EF_y = theta_EF_y_a;
theta_EF_z = theta_EF_z_a;
p_EF_x = p_EF_x_a;
p_EF_y = p_EF_y_a;
p_EF_z = p_EF_z_a;

theta_F2_x = theta_F2_x_a;
theta_F2_y = theta_F2_y_a;
theta_F2_z = theta_F2_z_a;
p_F2_x = p_F2_x_a;
p_F2_y = p_F2_y_a;
p_F2_z = p_F2_z_a;



%% Real values
% Torso
p_torso_x = zeros(1, tN);
p_torso_y = zeros(1, tN);
%p_torso_z = zeros(1, tN);
p_torso_z = 0.1 * (1+sin(f_torso*t - pi/2));

figure;
plot(t, p_torso_x); hold on;
plot(t, p_torso_y); hold on;
plot(t, p_torso_z); hold on;
title('Torso');

%theta_torso_x = zeros(1, tN);
theta_torso_x = pi/4 * (1+sin(f_arm*t));
%theta_torso_y = zeros(1, tN);
theta_torso_y = pi/6 * (1+sin(f_arm*t/2));
%theta_torso_z = zeros(1, tN);
theta_torso_z = pi/6 * (1-sin(2*f_arm*t));

figure;
plot(t, theta_torso_x); hold on;
plot(t, theta_torso_y); hold on;
plot(t, theta_torso_z); hold on;
title('Angle Torso');


% Shoulder
%theta_shoulder_a = zeros(1, tN);
theta_shoulder_a = pi/4 + pi/12 * sin(f_arm*t);
theta_shoulder_f = zeros(1, tN);
%theta_shoulder_f = pi/4 + pi/12 * sin(2*farm*t + pi/6);
theta_shoulder_i = zeros(1, tN);
%theta_shoulder_i = pi/4 + pi/12 * sin(4*farm*t + pi/3);

figure;
plot(t, theta_shoulder_a); hold on;
plot(t, theta_shoulder_f); hold on;
plot(t, theta_shoulder_i); hold on;
title('Shoulder');

% Elbow
%theta_elbow = zeros(1, tN);
theta_elbow = pi/2 + pi/4*sin(10*f_arm*t + pi/2);

figure;
plot(t, theta_elbow); hold on;
title('Elbow');

% Forearm
%theta_forearm = zeros(1, tN);
theta_forearm = pi/6 + pi/12*sin(5*f_arm*t + pi/2);

figure;
plot(t, theta_forearm); hold on;
title('Forearm');

vars = [p_torso_x;p_torso_y;p_torso_z;
    theta_torso_z;theta_torso_y;theta_torso_x;
    theta_shoulder_a;theta_shoulder_f;theta_shoulder_i;
    theta_elbow;
    theta_forearm]';



%% Real state
X_real = zeros(3 * size(vars, 2), tN);
i = 1;

for var=vars
    var2 = var';
    X_real(3 * (i - 1) + 1, :) = var2;
    X_real(3 * (i - 1) + 2, :) = deriv(var2, dt);
    X_real(3 * (i - 1) + 3, :) = deriv(deriv(var2, dt), dt);
    i = i + 1;
end
clearvars var var2 vars;


%% Observations
snr = 30;
Z = zeros(18, tN);
for i=1:tN
    Z(:, i) = hmeas(X_real(:, i));
end

for i=1:size(Z,1)
    Z(i, :) = awgn(Z(i, :), snr, 'measured');
end

figure;
subplot(3,1,1);
plot(t, Z(1:3, :));
title('Acc 0');

subplot(3,1,2);
plot(t, Z(7:9, :));
title('Acc 1');

subplot(3,1,3);
plot(t, Z(13:15, :));
title('Acc 2');


figure;
subplot(3,1,1);
plot(t, Z(4:6, :));
title('Gyr 0');

subplot(3,1,2);
plot(t, Z(10:12, :));
title('Gyr 1');

subplot(3,1,3);
plot(t, Z(16:18, :));
title('Gyr 2');


%% Covariance matrices
global P Q R;

sigma_v = 1;
P = eye(size(X_real, 1)) * sigma_v^2;

j = 1;
J = j*[dt^3/6;dt^2/2;dt];

Q = zeros(size(X_real, 1), size(X_real, 1));
for i=1:size(X_real, 1)/3
    Q(3*(i-1)+1:3*i, 3*(i-1)+1:3*i) = J*J';
end

sigma_acc = 0.01;
sigma_gyr = 0.01;
R1 = diag([ones(1, 3)*sigma_acc^2 ones(1, 3)*sigma_gyr^2]);
R2 = diag([ones(1, 3)*sigma_acc^2 ones(1, 3)*sigma_gyr^2]);
R3 = diag([ones(1, 3)*sigma_acc^2 ones(1, 3)*sigma_gyr^2]);
R = blkdiag(R1, R2, R3);



%% Parameter estimation

N = 20;

x0 = X_real(:, 1);

% params0 = [
%     0;-pi/2;0;
%     0;1;0;
%     0;0;-pi/3;
%     0;0;0;
%     pi/4;-pi/2;0;
%     0;1;-1.5;
%     0;pi/3;pi/6;
%     -0.25;0;0.75;
%     0;pi/6;pi/3;
%     0;0;-0.5;
%     pi/6;0;0;
%     -0.5;0.75;0];
% 
% params0 = -params0;
% 
% set_params(params0);
% [X_estimated, Z_estimated] = solve(Z, x0);
% res1 = [RMSE(Z', Z_estimated')'];
% 
% fun = param_error(Z, x0);
% res_fun1 = fun(params0);
% 
% params0 = -params0;
% 
% set_params(params0);
% [X_estimated, Z_estimated] = solve(Z, x0);
% res2 = [RMSE(Z', Z_estimated')'];
% 
% fun = param_error(Z, x0);
% res_fun2 = fun(params0);
% 
% disp([res1 res_fun1 res2 res_fun2]);
% 
% lbs = [-pi;-pi;-pi;0;0;0;
%     -pi;-pi;-pi;0;0;0;
%     -pi;-pi;-pi;0;0;0;
%     -pi;-pi;-pi;0;0;0;
%     -pi;-pi;-pi;0;0;0;
%     -pi;-pi;-pi;0;0;0];
% 
% ubs = [pi;pi;pi;100;100;100;
%     pi;pi;pi;100;100;100;
%     pi;pi;pi;100;100;100;
%     pi;pi;pi;100;100;100;
%     pi;pi;pi;100;100;100;
%     pi;pi;pi;100;100;100];
% 
% lbs = [];
% ubs = [];
% 
% 
% 
% params_T0 = [
%     0.1;-0.1;0;
%     0.05;0;0.2;];
% 
% % params_T0 = [0;0;0;0;0;0];
% 
% lbs_T0 = [-pi;-pi;-pi;-3;-3;-3];
% 
% ubs_T0 = [pi;pi;pi;3;3;3];
% 
% options = optimoptions(@lsqnonlin);
% options.Algorithm = 'trust-region-reflective';
% % options.Algorithm = 'levenberg-marquardt';
% options.DiffMinChange = 0.01;
% [params_estimated, resnorm] = lsqnonlin(param_error_T0(Z(:, 1:N), x0), params_T0, lbs_T0, ubs_T0, options);
% 
% disp("Params estimated");
% disp(params_estimated);



% % Global Search
% 
% error_fun = param_error_T0(Z(:, 1:N), x0);
% fun = @(params) sum(error_fun(params).^2);
% 
% problem = createOptimProblem('fmincon',...
%     'objective',fun,...
%     'x0',params_T0,...
%     'lb', lbs_T0,...
%     'ub', ubs_T0',...
%     'options',optimoptions(@fmincon,'Algorithm','sqp','Display','off','DiffMinChange', 0.1));
% 
% gs = GlobalSearch('Display','iter');
% 
% rng(14,'twister') % for reproducibility
% [x,fval] = run(gs,problem)
% 






%% State estimation

% Initial state
x0 = X_real(:, 1);

% Initialization
[X_estimated, Z_estimated] = solve(Z, x0);

% figure;
% subplot(3,1,1);
% plot(t, X_real(1, :)); hold on;
% plot(t, X_estimated(1, :)); hold on;
% title('Torso X');
% 
% subplot(3,1,2);
% plot(t, X_real(4, :)); hold on;
% plot(t, X_estimated(4, :)); hold on;
% title('Torso Y');
% 
% subplot(3,1,3);
% plot(t, X_real(7, :)); hold on;
% plot(t, X_estimated(7, :)); hold on;
% title('Torso Z');

figure;
subplot(3,1,1);
plot(t, X_real(10, :)); hold on;
plot(t, X_estimated(10, :)); hold on;
title('Angle Torso Z');

subplot(3,1,2);
plot(t, X_real(13, :)); hold on;
plot(t, X_estimated(13, :)); hold on;
title('Angle Torso Y');

subplot(3,1,3);
plot(t, X_real(16, :)); hold on;
plot(t, X_estimated(16, :)); hold on;
title('Angle Torso X');

figure;
subplot(3,1,1);
plot(t, X_real(19, :)); hold on;
plot(t, X_estimated(19, :)); hold on;
title('Shoulder Abduction');

subplot(3,1,2);
plot(t, X_real(22, :)); hold on;
plot(t, X_estimated(22, :)); hold on;
title('Shoulder Flexion');

subplot(3,1,3);
plot(t, X_real(25, :)); hold on;
plot(t, X_estimated(25, :)); hold on;
title('Shoulder Internal');

figure;
subplot(2,1,1);
plot(t, X_real(28, :)); hold on;
plot(t, X_estimated(28, :)); hold on;
title('Elbow');

subplot(2,1,2);
plot(t, X_real(31, :)); hold on;
plot(t, X_estimated(31, :)); hold on;
title('Forearm');

figure;
categories = {'Angle Torso Z', 'Angle Torso Y', 'Angle Torso X', 'Abduction', 'Flexion', 'Internal', 'Elbow', 'Forearm'};
x = categorical(categories);
x = reordercats(x, categories);
y = zeros(size(X_real, 1)/3 - 3, 1);
for i=4:size(X_real, 1)/3
    y(i - 3, 1) = RMSE(X_real(3*(i-1) + 1, :), X_estimated(3*(i-1) + 1, :)) * RAD2DEG;
end
bar(x, y);
title('RMSE');
ylabel("Error in °");



function [X_estimated, Z_estimated] = solve(Z, x0)
    global P Q R;

    X_estimated = zeros(size(x0, 1), size(Z, 2));
    Z_estimated = zeros(size(Z, 1), size(Z, 2));
    
    x = x0;
    X_estimated(:, 1) = x;
    
    for k=1:size(Z, 2)
        z = Z(:, k);

        % Run kalman filter
        [x,P] = ukf(@fstate, x, P, @hmeas, z, Q, R);

        % Store result
        X_estimated(:, k) = x;
        Z_estimated(:, k) = hmeas(x);
    end
end






function y = hmeas(X)
    global RAD2DEG g;

    X = X(:, 1);
    y = zeros(18, size(X, 2));
    
    dv_W = [0;0;-g;0;0;0];
    
    % IMU 0
    
    dv_WT = [X(3);X(6);X(9);0;0;0] + dv_W;
    
    v_WTz = [0;0;0;0;0;X(11)];
    dv_WTz = [0;0;0;0;0;X(12)] + dv_WT;
    
    v_TzTy = [0;0;0;0;X(14);0];
    dv_TzTy = [0;0;0;0;X(15);0];
    R_TzTy = roty(X(13) * RAD2DEG);
    dR_TzTy = X(14) * roty((X(13) + pi/2) * RAD2DEG);
    g_TzTy = hom(R_TzTy, [0;0;0]);
    dg_TzTy = hom(dR_TzTy, [0;0;0]);
    v_WTy = v_TzTy + inv_adjoint(g_TzTy) * v_WTz;
    dv_WTy = dv_TzTy + inv_adjoint(g_TzTy) * dv_WTz + inv_adjoint_der(g_TzTy, dg_TzTy) * v_WTz;
    
    v_TyTx = [0;0;0;X(17);0;0];
    dv_TyTx = [0;0;0;X(18);0;0];
    R_TyTx = rotx(X(16) * RAD2DEG);
    dR_TyTx = X(17) * rotx((X(16) + pi/2) * RAD2DEG);
    g_TyTx = hom(R_TyTx, [0;0;0]);
    dg_TyTx = hom(dR_TyTx, [0;0;0]);
    v_WTx = v_TyTx + inv_adjoint(g_TyTx) * v_WTy;
    dv_WTx = dv_TyTx + inv_adjoint(g_TyTx) * dv_WTy + inv_adjoint_der(g_TyTx, dg_TyTx) * v_WTy;
    
    v_TyTx = [0;0;0;X(17);0;0];
    dv_TyTx = [0;0;0;X(18);0;0];
    R_TyTx = rotx(X(16) * RAD2DEG);
    dR_TyTx = X(17) * rotx((X(16) + pi/2) * RAD2DEG);
    g_TyTx = hom(R_TyTx, [0;0;0]);
    dg_TyTx = hom(dR_TyTx, [0;0;0]);
    v_WTx = v_TyTx + inv_adjoint(g_TyTx) * v_WTy;
    dv_WTx = dv_TyTx + inv_adjoint(g_TyTx) * dv_WTy + inv_adjoint_der(g_TyTx, dg_TyTx) * v_WTy;
    
    v_WT = v_WTx;
    dv_WT = dv_WTx;
    
    global theta_T0_x theta_T0_y theta_T0_z;
    global p_T0_x p_T0_y p_T0_z;
    R_T0 = eul2rotm([theta_T0_z theta_T0_y theta_T0_x], 'ZYX');
    p_T0 = [p_T0_x;p_T0_y;p_T0_z];
    g_T0 = hom(R_T0, p_T0);
    
    v_W0 = inv_adjoint(g_T0) * v_WT;
    dv_W0 = inv_adjoint(g_T0) * dv_WT;

    y(1:3) = dv_W0(1:3);
    y(4:6) = v_W0(4:6);
    
    % IMU 1
    
    global theta_TS_x theta_TS_y theta_TS_z;
    global p_TS_x p_TS_y p_TS_z;
    R_TS = eul2rotm([theta_TS_z theta_TS_y theta_TS_x], 'ZYX');
    p_TS = [p_TS_x;p_TS_y;p_TS_z];
    g_TS = hom(R_TS, p_TS);
    
    v_WS = inv_adjoint(g_TS) * v_WT;
    dv_WS = inv_adjoint(g_TS) * dv_WT;

    v_SSa = [0;0;0;X(20);0;0];
    dv_SSa = [0;0;0;X(21);0;0];
    R_SSa = rotx(X(19) * RAD2DEG);
    dR_SSa = X(20) * rotx((X(19) + pi/2) * RAD2DEG);
    g_SSa = hom(R_SSa, [0;0;0]);
    dg_SSa = hom(dR_SSa, [0;0;0]);
    v_WSa = v_SSa + inv_adjoint(g_SSa) * v_WS;
    dv_WSa = dv_SSa + inv_adjoint(g_SSa) * dv_WS + inv_adjoint_der(g_SSa, dg_SSa) * v_WS;
     
    v_SaSf = [0;0;0;0;X(23);0];
    dv_SaSf = [0;0;0;0;X(24);0];
    R_SaSf = roty(X(22) * RAD2DEG);
    dR_SaSf = X(23) * roty((X(22) + pi/2) * RAD2DEG);
    g_SaSf = hom(R_SaSf, [0;0;0]);
    dg_SaSf = hom(dR_SaSf, [0;0;0]);
    
    v_WSf = v_SaSf + inv_adjoint(g_SaSf) * v_WSa;
    dv_WSf = dv_SaSf + inv_adjoint(g_SaSf) * dv_WSa + inv_adjoint_der(g_SaSf, dg_SaSf) * v_WSa;
     
    v_SfSi = [0;0;0;0;0;X(26)];
    dv_SfSi = [0;0;0;0;0;X(27)];    
    R_SfSi = rotz(X(25) * RAD2DEG);
    dR_SfSi = X(26) * rotz((X(25) + pi/2) * RAD2DEG);
    g_SfSi = hom(R_SfSi, [0;0;0]);
    dg_SfSi = hom(dR_SfSi, [0;0;0]);
    v_WSi = v_SfSi + inv_adjoint(g_SfSi) * v_WSf;
    dv_WSi = dv_SfSi + inv_adjoint(g_SfSi) * dv_WSf + inv_adjoint_der(g_SfSi, dg_SfSi) * v_WSf;
    
    v_WS = v_WSi;
    dv_WS = dv_WSi;
    
    global theta_S1_x theta_S1_y theta_S1_z;
    global p_S1_x p_S1_y p_S1_z;
    R_S1 = eul2rotm([theta_S1_z theta_S1_y theta_S1_x], 'ZYX');
    p_S1 = [p_S1_x;p_S1_y;p_S1_z];
    g_S1 = hom(R_S1, p_S1);
    
    v_W1 = inv_adjoint(g_S1) * v_WS;
    dv_W1 = inv_adjoint(g_S1) * dv_WS;

    y(7:9) = dv_W1(1:3);
    y(10:12) = v_W1(4:6);
    
    % IMU 2
    
    global theta_SE_x theta_SE_y theta_SE_z;
    global p_SE_x p_SE_y p_SE_z;
    R_SE = eul2rotm([theta_SE_z theta_SE_y theta_SE_x], 'ZYX');
    p_SE = [p_SE_x;p_SE_y;p_SE_z];
    g_SE = hom(R_SE, p_SE);
    
    v_WE = inv_adjoint(g_SE) * v_WS;
    dv_WE = inv_adjoint(g_SE) * dv_WS;
    
    v_EEy = [0;0;0;0;X(29);0];
    dv_EEy = [0;0;0;0;X(30);0];
    R_EEy = roty(X(28) * RAD2DEG);
    dR_EEy = X(29) * roty((X(28) + pi/2) * RAD2DEG);
    g_EEy = hom(R_EEy, [0;0;0]);
    dg_EEy = hom(dR_EEy, [0;0;0]);
    v_WEy = v_EEy + inv_adjoint(g_EEy) * v_WE;
    dv_WEy = dv_EEy + inv_adjoint(g_EEy) * dv_WE + inv_adjoint_der(g_EEy, dg_EEy) * v_WE;
    
    v_EyEz = [0;0;0;0;0;X(32)];
    dv_EyEz = [0;0;0;0;0;X(33)];
    R_EyEz = rotz(X(31) * RAD2DEG);
    dR_EyEz = X(32) * rotz((X(31) + pi/2) * RAD2DEG);
    g_EyEz = hom(R_EyEz, [0;0;0]);
    dg_EyEz = hom(dR_EyEz, [0;0;0]);
    v_WEz = v_EyEz + inv_adjoint(g_EyEz) * v_WEy;
    dv_WEz = dv_EyEz + inv_adjoint(g_EyEz) * dv_WEy + inv_adjoint_der(g_EyEz, dg_EyEz) * v_WEy;
    
    v_WE = v_WEz;
    dv_WE = dv_WEz;
    
    global theta_EF_x theta_EF_y theta_EF_z;
    global p_EF_x p_EF_y p_EF_z;
    R_EF = eul2rotm([theta_EF_z theta_EF_y theta_EF_x], 'ZYX');
    p_EF = [p_EF_x;p_EF_y;p_EF_z];
    g_EF = hom(R_EF, p_EF);
    
    v_WF = inv_adjoint(g_EF) * v_WE;
    dv_WF = inv_adjoint(g_EF) * dv_WE;
    
    global theta_F2_x theta_F2_y theta_F2_z;
    global p_F2_x p_F2_y p_F2_z;
    R_F2 = eul2rotm([theta_F2_z theta_F2_y theta_F2_x], 'ZYX');
    p_F2 = [p_F2_x;p_F2_y;p_F2_z];
    g_F2 = hom(R_F2, p_F2);
    
    v_W2 = inv_adjoint(g_F2) * v_WF;
    dv_W2 = inv_adjoint(g_F2) * dv_WF;
    
    y(13:15) = dv_W2(1:3);
    y(16:18) = v_W2(4:6);
end


function y = fstate(X)
    global dt;
    A = [1 dt dt*dt/2; 0 1 dt; 0 0 1];
    AA = zeros(size(X, 1), size(X, 1)); % Matrix with A blocks on the diagonal
    for i = 1:size(X, 1)/3
        AA(3*(i-1) + 1:3*i, 3*(i-1) + 1:3*i) = A;
    end
    
    y = AA * X;
end









function y = deriv(x, dt)
    y = zeros(1, size(x, 2));
    for i=1:size(x, 2) - 1
        y(1, i) = (x(1, i+1) - x(1, i)) / dt;
    end
end

function y = RMSE(x, x0)
    y = sqrt(mean((x-x0).^2));
end

function y = RMSEs(x, x0)
    y = RMSE(x, x0) ./ mean(x0);
end


function y = set_params(params)
    global theta_T0_x theta_T0_y theta_T0_z;
    global p_T0_x p_T0_y p_T0_z;
    global theta_TS_x theta_TS_y theta_TS_z;
    global p_TS_x p_TS_y p_TS_z;
    global theta_S1_x theta_S1_y theta_S1_z; 
    global p_S1_x p_S1_y p_S1_z;
    global theta_SE_x theta_SE_y theta_SE_z;
    global p_SE_x p_SE_y p_SE_z;
    global theta_EF_x theta_EF_y theta_EF_z;
    global p_EF_x p_EF_y p_EF_z;
    global theta_F2_x theta_F2_y theta_F2_z;
    global p_F2_x p_F2_y p_F2_z;


    theta_T0_x = params(1);
    theta_T0_y = params(2);
    theta_T0_z = params(3);
    p_T0_x = params(4);
    p_T0_y = params(5);
    p_T0_z = params(6);

    theta_TS_x = params(7);
    theta_TS_y = params(8);
    theta_TS_z = params(9);
    p_TS_x = params(10);
    p_TS_y = params(11);
    p_TS_z = params(12);

    theta_S1_x = params(13);
    theta_S1_y = params(14);
    theta_S1_z = params(15);
    p_S1_x = params(16);
    p_S1_y = params(17);
    p_S1_z = params(18);

    theta_SE_x = params(19);
    theta_SE_y = params(20);
    theta_SE_z = params(21);
    p_SE_x = params(22);
    p_SE_y = params(23);
    p_SE_z = params(24);

    theta_EF_x = params(25);
    theta_EF_y = params(26);
    theta_EF_z = params(27);
    p_EF_x = params(28);
    p_EF_y = params(29);
    p_EF_z = params(30);

    theta_F2_x = params(31);
    theta_F2_y = params(32);
    theta_F2_z = params(33);
    p_F2_x = params(34);
    p_F2_y = params(35);
    p_F2_z = params(36);
end



function y = param_error(Z, x0)
    function y = error(params)
        set_params(params);
        
        [a, Z_estimated] = solve(Z, x0);
        
        ZZ = zeros(9, size(Z, 2));
        ZZ(1:3, :) = Z(4:6, :);
        ZZ_estimated(1:3, :) = Z_estimated(4:6, :);
        ZZ(4:6, :) = Z(10:12, :);
        ZZ_estimated(4:6, :) = Z_estimated(10:12, :);
        ZZ(7:9, :) = Z(16:18, :);
        ZZ_estimated(7:9, :) = Z_estimated(16:18, :);
        
        y = sum(RMSE(ZZ, ZZ_estimated));
        
        disp(sum(y.^2));
    end
    y = @error;
end

function y = param_error_T0(Z, x0)
    function y=error(params)
        global theta_T0_x theta_T0_y theta_T0_z;
        global p_T0_x p_T0_y p_T0_z;
        
        theta_T0_x = params(1);
        theta_T0_y = params(2);
        theta_T0_z = params(3);
        p_T0_x = params(4);
        p_T0_y = params(5);
        p_T0_z = params(6);
        
        [a, Z_estimated] = solve(Z, x0);
        
        aux = zeros(2, size(Z,2));
        aux(1, :) = sum((Z_estimated(1:3, :) - Z(1:3, :))./mean(Z(1:3, :)')'.^2);
        aux(2, :) = sum((Z_estimated(4:6, :) - Z(4:6, :))./mean(Z(4:6, :)')'.^2);
        
        y = sum(aux);
        
        disp(params);
        disp(sum(y.^2));
    end

    y = @error;
end









%% Helpers
function y = hom(R, p)
    y = [R p; 0 0 0 1];
end

function y = adjoint(g)
    R = rot_hom(g);
    p = tra_hom(g);
    y = [R R*wee_rot(p); zeros(3,3) R];
end

function y = adjoint_der(g, g_der)
    R = rot_hom(g);
    p = tra_hom(g);
    
    R_der = rot_hom(g_der);
    p_der = tra_hom(g_der);
    
    y = [R_der R_der*wee_rot(p)+R*wee_rot(p_der);zeros(3,3) R_der];
end

function y = inv_adjoint(g)
    R = rot_hom(g);
    p = tra_hom(g);
    y = [R' -R'*wee_rot(p); zeros(3,3) R'];
end

function y = inv_adjoint_der(g, g_der)
    R = rot_hom(g);
    p = tra_hom(g);
    
    R_der = rot_hom(g_der);
    p_der = tra_hom(g_der);
    
    y = [R_der' -R_der'*wee_rot(p)-R'*wee_rot(p_der); zeros(3,3) R_der'];
end


function y = wee_rot(w)
    z = zeros(1, size(w, 2));
    y = [z -w(3, :) w(2, :);w(3, :) z -w(1, :); -w(2, :) w(1, :) z];
end

function y = vee_rot(r)
    y = [r(3, 2); r(1,3); r(2,1)];
end

function y = vee_hom(g)
    y = [tra_hom(g); vee_rot(rot_hom(g))];
end

function y = rot_hom(g)
    y = g(1:3,1:3);
end

function y = tra_hom(g)
    y = g(1:3, 4);
end







function y = rot_matrix_torso(theta)
    y = euler_x(theta(3)) * euler_y(theta(2)) * euler_z(theta(1));
end

function y = rot_matrix_torso_der(theta, theta_der)
    y = euler_x(theta(3))                   * euler_y(theta(2))                     * euler_z_der(theta(1), theta_der(1)) + ...
        euler_x(theta(3))                   * euler_y_der(theta(2), theta_der(2))   * euler_z(theta(1)) + ...
        euler_x_der(theta(3), theta_der(3)) * euler_y(theta(2))                     * euler_z(theta(1));
end

% function y = rot_matrix_der_der(theta, theta_der, theta_der_der)
%     y = euler_z(theta(3)) * euler_y(theta(2)) * euler_x_der_der(theta(1), theta_der(1), theta_der_der(1)) + ...
%         euler_z(theta(3)) * euler_y_der(theta(2), theta_der(2)) * euler_x_der(theta(1), theta_der(1)) + ...
%         euler_z_der(theta(3), theta_der(3)) * euler_y(theta(2)) * euler_x_der(theta(1), theta_der(1)) + ...
%         euler_z(theta(3)) * euler_y_der(theta(2), theta_der(2)) * euler_x_der(theta(1), theta_der(1)) + ...
%         euler_z(theta(3)) * euler_y_der_der(theta(2), theta_der(2), theta_der_der(2)) * euler_x(theta(1)) + ...
%         euler_z_der(theta(3), theta_der(3)) * euler_y_der(theta(2), theta_der(2)) * euler_x(theta(1)) + ...
%         euler_z_der(theta(3), theta_der(3)) * euler_y(theta(2)) * euler_x_der(theta(1), theta_der(1)) + ...
%         euler_z_der(theta(3), theta_der(3)) * euler_y_der(theta(2), theta_der(2)) * euler_x(theta(1)) + ...
%         euler_z_der_der(theta(3), theta_der(3), theta_der_der(3)) * euler_y(theta(2)) * euler_x(theta(1));
% end

function y = euler_x(theta)
    y = [1 0 0; 0 cos(theta) -sin(theta); 0 sin(theta) cos(theta)];
end

function y = euler_y(theta)
    y = [cos(theta) 0 sin(theta); 0 1 0; -sin(theta) 0 cos(theta)];
end

function y = euler_z(theta)
    y = [cos(theta) -sin(theta) 0; sin(theta) cos(theta) 0; 0 0 1];
end


function y = euler_x_der(theta, theta_der)
    y = theta_der * euler_x(theta + pi/2);
end

function y = euler_y_der(theta, theta_der)
    y = theta_der * euler_y(theta + pi/2);
end

function y = euler_z_der(theta, theta_der)
    y = theta_der * euler_z(theta + pi/2);
end

function y = euler_x_der_der(theta, theta_der, theta_der_der)
    y = theta_der_der * euler_x(theta + pi/2) + (theta_der^2)*euler_x(theta + pi);
end

function y = euler_y_der_der(theta, theta_der, theta_der_der)
    y = theta_der_der * euler_y(theta + pi/2) + (theta_der^2)*euler_y(theta + pi);
end

function y = euler_z_der_der(theta, theta_der, theta_der_der)
    y = theta_der_der * euler_z(theta + pi/2) + (theta_der^2)*euler_z(theta + pi);
end