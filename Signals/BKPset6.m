%% Benjamin Kaplan - PS6
clc;
clear all;
close all;
%% Question 1
A = [-1/5 , 3/10 ; 1 ,0];
B = [1;0];
C = [9/25 56/100];
D = [1/5];
[Y,X] = ss2tf(A,B,C,D)

At = A';
Bt = C';
Ct = B';
Dt = D';
[Yt,Xt] = ss2tf(At,Bt,Ct,Dt)

[a,b,c,d] = tf2ss([2 4 5],[10 2 -3])
fprintf('This is the same!\n');
T = [3 7; 2 5];

at = T*a*inv(T);
bt = T*b;
ct = c*inv(T);
dt = d;

syms z;
H = ct*((z*eye(2)-at)^-1)*bt+dt;
fprintf('Simplified H(z): ');
simplify(H) % This returns the same H(z) that I started with
[zero poles k]=tf2zp([2 4 5], [10 2 -3]);
fprintf('Eigen values of A: ')
eig(A)
fprintf('Eigen values of A^T: ')
eig(At)
fprintf('Eigen values of T*A*T^-1: ')
eig(at)
poles % All of these are the same

ApowerN = iztrans(z*((z*eye(2)-A)^-1))

A^10 % These are the same!
fprintf('Max difference is: %.20f\n',max(max(A^10 -vpa(subs(ApowerN,10)))));

%% Question 2
syms lambda
syms t
M = [1,lambda, (lambda^2), (lambda^3),(lambda^4),(lambda^5);
     0,1     , 2*lambda, 3*lambda^2, 4*lambda^3, 5*lambda^4;
     0,0     , 2 , 6*lambda, 12*lambda^2, 20*lambda^3; 
     1,lambda, lambda^2, lambda^3,lambda^4,lambda^5;
     1,lambda, lambda^2, lambda^3,lambda^4,lambda^5;
     1,lambda, lambda^2, lambda^3,lambda^4,lambda^5];
 f = [exp(-5*t);
      t*exp(-5*t);
      (t^2)*exp(-5*t);
      exp((-2+j*6)*t);
      exp((-2-j*6)*t);
      exp(3*t)];
  eigs = [-5, -5, -5, -2+(j*6), -2-(j*6), 3];
  Msubed = ones([6 6]);
  for k = 1:6
      Msubed(k,:) = subs(M(k,:),eigs(k));
  end
  
  r = inv(Msubed)*f;
  
  etotheAt = syms(zeros(6));
  randMat = rand(6);
  for q = 1:6
      etotheAt(1,q) = etotheAt(1,q) + r(q,1)*(randMat*diag(eigs)*inv(randMat))^(q-1);
  end 