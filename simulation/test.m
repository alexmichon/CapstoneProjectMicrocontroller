clc
clear all

syms t11 t12 t13 
syms dt11 dt12 dt13
syms ddt11 ddt12 ddt13
assume(t11,'real');assume(t12,'real');assume(t13,'real');
assume(dt11,'real');assume(dt12,'real');assume(dt13,'real');
assume(ddt11,'real');assume(ddt12,'real');assume(ddt13,'real');
syms p1x p1y p1z
assume(p1x,'real');assume(p1y,'real');assume(p1z,'real');
pos = [p1x p1y p1z]';

syms t21 t22 t23
syms dt21 dt22 dt23
assume(t21,'real');assume(t22,'real');assume(t23,'real');
assume(dt21,'real');assume(dt22,'real');assume(dt23,'real');

syms t31
assume(t31,'real')
syms dt31
assume(dt31,'real')



[g1,R1,p1] = G_world_torso([t11 t12 t13],pos);
R_dot = diff(R1,t11)* dt11 + diff(R1,t12)* dt12 + diff(R1,t13)* dt13;
dp1 = diff(p1,t11)* dt11 + diff(p1,t12)* dt12 + diff(p1,t13)* dt13;
trans = simplify(-R_dot*p1 + dp1);
W_H = simplify(R_dot*(R1'));
W = H_toN(W_H);
accW = simplify(diff(W,t11)* dt11 + diff(W,t12)* dt12 + diff(W,t13)* dt13 ...
       +diff(W,dt11)* ddt11 + diff(W,dt12)* ddt12 + diff(W,dt13)* ddt13);
accV = simplify(diff(trans,t11)* dt11 + diff(trans,t12)* dt12 + diff(trans,t13)* dt13 ...
   +diff(trans,dt11)* ddt11 + diff(trans,dt12)* ddt12 + diff(trans,dt13)* ddt13);
V = simplify([accV;accW]);






% [g1,R1,p1] = G_ua_fa(t31,pos);
% R_dot = diff(R1,t31)*dt31;
% w_H = R_dot*(R1');


% [g2,R2,p2] = G_world_torso([t21 t22 t23],pos);
% [g3,R3,p3] = G_ua_fa(t31,pos);




