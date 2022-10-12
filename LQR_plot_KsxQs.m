%% Program Info

%%% Author: Jacob Clark
%%% Last Date Updated: 9/12/2021

%%% V.1 
%%% Defined system matrixes

%%% V.2
%%% Looped through and Plotted LQR

%%% V.3
%%% Added K and functions to match_up with simulink file:
%%% q_qube2_Cube_Simulation_With_Impulse

%% Defined system, input and output matrix %%

%%% System Matrix as defined by problem
A=[ 0 0 1 0; 0 0 0 1; 0 149.2751 -0.0104 0; 0 261.6091 -0.0103 0];

%%Input Matrix as defined by problem
B=[0; 0; 49.7275; 49.1493];

%%Output matrix, our outputs from the quasar cube are only theta and alpha
C=[1 0 0 0; 0 1 0 0]; 

eig(A); %% eigen values of the open system %%

%%% Defining D in state matrix, used to find the tf equations
D=[0;0;];

%%% Defining R to be set to 1
R=1;

%%% Defining the transfer functions that will be the plants to theta and
%%% alpha
[Num Den]=ss2tf(A,B,C,D);
Theta_num = [Num(1,:)];
Alpha_num = [Num(2,:)];
Characteristic=[Den];
Alpha_TF=tf(Alpha_num,Characteristic)
Theta_TF=tf(Theta_num,Characteristic)

%%iteration is used to define how far the weighting of Q will go past 1 in
%%the program. Change as desired
iteration = 1000;

%%matrix built to record the eigen values of the closed loop system throught he iterations
RecEig=zeros(4,iteration,4);

%%Matrix built to record the all K values of an iteration 
RecK=zeros(4,iteration,4);

%%Matrix built to record all values of a K for one change in Q to be plotted
Kplot=zeros(4, iteration);

%% Calculation of the given input setup below

%%% Start of the loop qlocation to determine which weight in Q being
%%% changed and recorded
for qlocation=1:1:4

    %%% loop through the qvalue for the weight   
    for qvalue=1:1:iteration;
        %%% resets Q
        Q=eye(4);

        Q(qlocation,qlocation)=qvalue;  
        K=lqr(A, B, Q, R);
        D=[0;0];
        K;

        %%% Storing the eigen values of the closed location to redistributed to in
        %%% a matrix location later
        EigDUM=eig(A-B*K);

        %%% Loop through the recording locations to fill in the record matrixes
        for Recording=1:1:4
            RecK(Recording,qvalue,qlocation)=K(Recording);
            Kplot(Recording,qvalue)=K(Recording);
            RecEig(Recording,qvalue,qlocation)=EigDUM(Recording);
            %%% end of recording loop
        end
        %%% End of one iteration for qvalue
    end

%%% Stating a new table
figure
    %%% Loop to plot the four different gains
    for KGainN=1:1:4
        y=1:1:iteration;
        plot(y,Kplot(KGainN,y));
        hold on;
      end

%%% Adding lables to tables
legend('K-theta', 'K-alpha', 'K-thetadot', 'K-alphadot')
xlabel('Q weight')
ylabel('K Gain')
hold off

%%% End of the qlocation
end

%% Code to find Define Ks in for use in the simulink

Qfinal=[10 0 0 0; 0 10 0 0; 0 0 1 0; 0 0 0 1];
K_n=lqr(A, B, Qfinal, R);
K_theta = K_n(1);
K_alpha = K_n(2);
K_theta_dot = K_n(3);
K_alpha_dot = K_n(4);