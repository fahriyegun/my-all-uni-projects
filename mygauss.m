
function [singular, x] = mygauss (A,b)

%look A's size
%row m, column n
[m,n]=size(A);
%if m doesnt equal to n,not be solved.
if m~=n
     error('Matrix is not square');
     singular=1;
end

singular =0;
for k = 1 : n-1
s=zeros(n,1);
 %%%%  fýnd max absolute value in every row.
for i=k:n                         
    s_max=0;
    for j=k:n
         w = abs(A(i,j));
        if w>s_max
            s_max=w;
        end
        
    end
    %save max values in s array, n sizes
    s(i)=s_max;
end

temp=zeros(n,1);

%divide one element by row's max value in every row
for i=k:n
    temp(i)=A(i,k)/s(i);
end

s_max=0;
p=1;
%find index of maximum quotient
for i=1:n
    if temp(i)>s_max
        s_max=temp(i);
        p=i;
    end
end

%swap between maximum quotient and above row
t=A(k,:);
A(k,:)=A(p,:);
A(p,:)=t;

t=b(k);
b(k)=b(p);
b(p)=t;


%make 0 following row with operations 
   for i = k+1 : n
      
     m = A(i,k) / A(k,k);
      for j = 1 : n
         A(i,j) = A(i,j) - m*A(k,j);
      end
      
	b(i) = b(i) - m*b(k);
   end
end

%solve with backward subsitition 
%A*x=b
%x=b/A
%save x values in x array.
x = zeros(n,1);
x(n) = b(n) / A(n,n);
for i = n-1 : -1 : 1;
   u = b(i);
   for j = i+1 : n
      u = u - A(i,j)*x(j);
   end
   x(i) = u / A(i,i);
end
x
end