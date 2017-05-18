output=0;
      %PERIOD OF FUNCTIONS : T
      %t=  [-3: 0.01 : 3];
      %t=  [-10: 0.01 : 10];
      t=  [-50: 0.01 : 50];
      
      for k = -50 : 1 : 50
          if(k~=0)
              %first function
              f=exp((1i*2*pi*k*t)/20);
              ak=(25/((k^2)*(pi^2)))*((cos((k*pi)/10))-(cos((3*k*pi)/10)));
             
              %second function
              %f=exp((1i*2*pi*k*t)/6);
              %ak=(24/(k*pi))*(sin(2*pi*k)/3)+(36/(pi^2*k^2))*(cos((2*pi*k)/3))-(36/(pi^2*k^2));
            
              output = output + ak*f;
              
          else
              output = output + 1*exp((1i*2*pi*k*t)/20);     %first func
              %output = output + (4/3)*exp((1i*2*pi*k*t)/6);          %second func
          end
      end
  
  plot(real(output))