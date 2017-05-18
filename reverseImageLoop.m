im=imread('birds2.jpg');
rs=250;%row start
re=460;%row end
cs=175;%column start
ce=490;%column end
x=(re-rs)/2;
y=(cs-ce)/2;

for i=rs:x
    tempx=re;
    for j=cs:y
        tempy=ce;
        temp=im(i,j,:);
        im(i,j,:)=im(tempx,tempy,:);
        im(tempx,tempy,:)=temp;
        tempy=tempy-1;
        
    end
    tempx=tempx-1;
end
imshow(im)

    