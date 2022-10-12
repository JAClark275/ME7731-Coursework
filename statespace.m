
clear all

% ###############  ACTIVE SUSPENSION SYSTEM ###############
% ################ Prepared by Y. Zweiri ##################
% ###############MODEL PARAMETERS###############

ks =900 ;% or 1040 Suspension Stiffness (N/m) 
kus = 2500;% Tire stiffness (N/m)
ms = 2.45;% or 2.5 Sprung Mass (kg) 
mus = 1;% Unsprung Mass (kg)
bs = 7.5;% Suspension Inherent Damping coefficient (sec/m)----
bus = 5;% Tire Inhenrent Damping coefficient (sec/m)--------
%This section sets the A,B,C and D matrices for the Active Suspension model.

A = [ 0 1 0 -1;-ks/ms -bs/ms 0 bs/ms;0 0 0 1;ks/mus bs/mus -kus/mus -(bs+bus)/mus];
B = [0  0; 0 1/ms; -1  0; bus/mus -1/mus];
C = [ 1 0 0 0; -ks/ms -bs/ms 0 bs/ms];
D = [0 0;0 1/ms] ;


    
