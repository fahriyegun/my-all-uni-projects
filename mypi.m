%FAHRÝYE GÜN      150112025
%ÞEBNEM KARAKILIÇ 150112058

function [ pi_ ] = mypi( numpoints )
x=rand([1 numpoints]);%take random x,y coordinate
y=rand([1 numpoints]);
counter=0;
f=(x.*x)+(y.*y);  %circle equation -> x^2+y^2
for i=1:numpoints
   if  f(i)<=1%inside in circle
        counter=counter+1;%successful 
    end
end
   pi_=(counter*4)/numpoints;%return output value that approximately pi value
   

end
