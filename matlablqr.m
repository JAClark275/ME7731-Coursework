A=[ 0 0 1 0; 0 0 0 1; 0 149.2751 -0.0104 0; 0 261.6091 -0.0103 0];
B=[0; 0; 49.7275; 49.1493];
C=[1 0 0 0; 0 1 0 0;];
eig(A); %% eigen values of the open system %%
Q=eye(4);
Q(1,1)=4; %%only one to effect theta high effect theta, low effect all others%%8
Q(2,2)=0.8; %% low effect on all but theta%%0
Q(3,3)=3; %% high effect alpha, theta dot, alpha dot  no affect on theta%%1
Q(4,4)=1; %% no affect on the theat, high affect on alpha and alpha dot%%.7
R=1;
K=lqr(A, B, Q, R);
D=[0;0;];
[Num Den]=ss2tf(A,B,C,D)
arm_num1=[Num(1,:)]
arm_den1=[Den]
pend_num1=[Num(2,:)]
pend_den1=[Den]

ArmTheta=tf(arm_num1,arm_den1)
PendAlpha=tf(arm_num1,arm_den1)

K;
EigDUM=eig(A-B*K);%%iegen values of the closed system%%

%%G=tf(1, [1 72.4605])*tf(1, [1 9.926])*tf(1, [1 7.851])*tf(1, [1 1.0045])