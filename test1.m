largeImage=imread('largeImage.png');%reads image
large=rgb2gray(largeImage);%conver to gray

t1=imread('t1.jpg');
t2=imread('t2.jpg');
t3=imread('t3.jpg');
temp1=rgb2gray(t1);
temp2=rgb2gray(t2);
temp3=rgb2gray(t3);
template = (temp1+temp2+temp3)./3; %take average
%imshow(template)
I=uint16(large);% convert 16bit because that give more true result
T=uint16(template); 


largeImageSize=size(I); %get size
TemplateSize=size(T);

m=largeImageSize(1);
n=largeImageSize(2);
p=TemplateSize(1);
q=TemplateSize(2);

image(imread('largeImage.png'));
hold on;

for i=1:m-p
   for j=1:n-q
      corr(i,j)=correlate(T,I (i:i+p-1, j:j+q-1));
        
     if(corr(i,j)>0.63);
        rectangle('Position',[j,i,q,p],'EdgeColor','Y','LineWidth',2.5);
     end
   end
end     

