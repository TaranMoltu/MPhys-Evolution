% BinarySplitter.m
% Reads in line x of the file of genomes which is in the form
% 001,010,010 etc
% then changes it such that the matrix line{a} reads
% 0 0 1 etc
% 0 1 0 etc
% 0 1 0 etc
% Note that line is an array of structs, where each struct is rows across
% and 3 cols down.
% This can then be sampled using the dimensionality reduction toolbox. By
% doing this for 1<=x<=rows we get 5000 graphs for how the binary data
% evolves in space, which we can animate and hopefully see clusters form in
% 
% M. Williams 11/12/2012

% Housekeeping: read in the data in the traditional method

[FileName,PathName,FilterIndex] = uigetfile('*.dat');
filename = fullfile(PathName, FileName);
genomematrix = csvread(filename);

[rows, cols] = size(genomematrix); %rows is number of rows etc

% Now start going across each row and saving to a new struct line{i}
% number)

%DEBUG: doing for one to start with, generation 1 is as good as any
for i=1:1
    for j=1:cols
        if numel(num2str(genomematrix(i,j)))<8 %Assumes 8D array. Better practice would be to work out the size of the largest value or ask for it
           %Code to pad with zeroes goes here 
           padsize = 8 - numel(num2str(genomematrix(i,j))); %Assumes 8 again
           pad=zeros([1,padsize]);
           %Convert pad to string and remove spaces
           pad=num2str(pad);
           pad=regexprep(pad,'[^\w'']',''); %Use regexp from http://www.mathworks.co.uk/matlabcentral/newsreader/view_thread/158554 to remove space
           temp= [pad, num2str(genomematrix(i,j))];
        else
            temp= num2str(genomematrix(i,j));
        end
        for k = 1:8 %Assumes 8
            line_1(j,k) = str2num(temp(k));
        end
    end
end
