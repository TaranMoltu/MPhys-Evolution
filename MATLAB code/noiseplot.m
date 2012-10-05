%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% noiseplot.m
% Author: M. Williams 2/10/12
% This file reads in data generated by our C++ project and outputs a graph
% based on figure 1 of Rogers et al. It then does this in the form of a 
% grayscale histogram.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%filename = input('What is the filename for the data including extension?: ');
filename = 'log.dat';
datamatrix = csvread(filename);
[rows, cols] = size(datamatrix); %rows is number of rows etc

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Data has been read in. We now want to start implementing histogram
% functionality. To do this, we examine each generation and work out how
% many fit in a 'bucket'. We know that the range of values is from -pi to
% pi so we can ask the user how many buckets they want and divide the range
% up. Then count how many fall into a bucket.
% Useful to know: buckets = number of buckets wanted by user
% bucketsize = the size per bucket
% bucketmax = a vector showing how far across to go for each bucket
%
% TODO: (optional) range assumed is -pi to pi, we could implement option
% for user to enter min and max.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

buckets = input('How many buckets would you like to use? ');
bucketsize = (2*pi)/buckets;

%Declare max size for first bucket outside loop
bucketmax(1)= (-1*pi)+bucketsize;

%Now with the size of each bucket known we need to start the count of the
%number of values that fall in each bucket per generation.
%bucketmatrix is a matrix that has as many across as there are buckets and
%down as generations. The number in each cell represents the number of
%cells fitting in the range defined in bucketmax. Going across means bigger
%range, going down means further time step.
bucketmatrix = zeros(buckets+1,rows);
for i=1:rows
    for j=1:cols
        if datamatrix(i,j)~=0
            bucket = floor((datamatrix(i,j)+pi)/bucketsize)+1;
            bucketmatrix( bucket,i) = bucketmatrix( bucket,i)+1;
        end
    end
end

disp('sorted');

%We now have the number that fits into every bucket for all generations. We
%hence want to convert these to a grayscale value. This can be done by
%working out the fraction of the total that are in each bucket for the
%generation and then multiplying by 255. This means that if a bucket
%contains all the numbers for a generation, its hex code will be 255 and so
%it will be white. Conversely, if it contains none then its hex code will
%be 000 and so black. The darker a bucket is, the emptier it is.

%Work around for issue 17: work out how many are alive in each generation
%using another for loop
numberalive = max(bucketmatrix);
bignumberalive=zeros(buckets+1,rows);
%WARNING: see issue #17, there is a problem with this method.
for i=1:buckets
    bignumberalive(i,:)=numberalive;
end
bucketfractions = bucketmatrix./bignumberalive.*255;

%We now need to start graphing these colours
%ia=ones(200,200).*255;
output = uint8(bucketfractions);
 imwrite(output, 'output.png', 'png');
% 
% [fractionrows, fractioncols] = size(bucketfractions);
% ia(1:fractionrows, 1:fractioncols) = bucketfractions;
% 
% imshow(ia(1:fractionrows, 1:fractioncols));
disp('End of program');