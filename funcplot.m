%FAHRÝYE GÜN      150112025
%ÞEBNEM KARAKILIÇ 150112058

x=[-pi:2*pi/1000:pi];%range: from -pi to p, 1000 intervals.
fx=2*cos(x.^2/2).*exp(1).^(0.6.*x);%f(x)
plot(x,fx,'r.');%plot of f(x)