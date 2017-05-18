% FAHRÝYE GÜN       150112025
% ÞEBNEM KARAKILIÇ  150112058

function plotpder (coef, x1, x2, numpoints)
%THIS FUNCTION GIVE US TWO PLOT IN ONE GRAPH.
%ONE PLOT IS A POLYNOM FUNCTION'S PLOT BETWEEN X1 TO X2.
%OTHER IS FIRST DEGREE DERIVATIVE FUNCTION OF ABOVE POLYNOM FUNCTION'S PLOT
%BETWEEN X1 TO X2
x=linspace(x1,x2,numpoints);%plot range is from x1 to x2,numpoints intervals.
y1=polyval(coef,x);%polynom function evalution
der=polyder(coef,1);%turn to derivative equation of 1.degree
y2=polyval(der,x);% derivative function evalution
hold on;
plot(x,y1,'m*');%plot of f(x)
plot(x,y2,'co');%plot of derivate of f(x)
hold off;
%labels...
xlabel('X axis');                    
ylabel('Y axis');                                          
title('Graph of function and derivative of funtion'); 
legend('F(x)', 'Derivative of F(x)');


end