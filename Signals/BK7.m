%% Benjamin Kaplan - PS 7

%% Question 1 
clc
clear all
close all
DCgain = 20*log10( (0+100)/(0^2 +0 + 49))
Q= 7/1

bode(tf([0 1 100],[1 1 49]))

%% Question 2
H = (10*j+10)*((10*j+30)^2)/((10*j+4)*(10*j+100))
angle(H)*180/pi

%% Question 5
figure 
s1 = tf([0 1 2],[1 4.8 4])
s2 = tf([0 -1 2],[1 4.8 4])
class(s1);
get(s1);
hold on
step(s1,s2); % unit step response of s1 and s2
legend('s1', 's2') 
text('s2 has a negative amplitude dip towards the beginning');
hold off

