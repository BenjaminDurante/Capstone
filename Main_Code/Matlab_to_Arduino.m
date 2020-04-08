%Matlab to Arduino data upload
%Any questions please contact benjamin.durante@ucalgary.ca
clear 
clc

%Uploads Excel Sheet that has been preformatted
T = readtable('Comp_Data_autocross.xlsx');
%stackedplot(T);
A = table2array(T); %Converts the table to an array

% Code to read and upload vehicle speed to the Arduino
ar = serial('COM4','BaudRate',9600); 
%May need to change the COM port depending on your computer

%Begins the transfer to the Arduino, one element at a time
fopen(ar);
for (i=1:length(A))
    A(i,2)
    fprintf(ar,'%s',char(A(i,2)));
    pause(20/1000); %Data rate in seconds
end
fclose(ar);
%Ends the transfer of data to the Arduino
