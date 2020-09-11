#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;


/*Function 'header(string)' to add required header in resultant CSV file , takes the name of file as an argument
  if file is not exist it makes a file with the given name in the same folder*/


void header(string str)
{
    ofstream myFile;

    myFile.open(str,ios::app);

    myFile<<"Order Number"<<", ";
    myFile<<"Profit/Loss(%)"<<", ";
    myFile<<"Transferred Amount"<<", ";
    myFile<<"Total MarketPlace Charge"<<", ";



    myFile.close();

}



/*function which takes the two string type argument which is basically the file name, first file name from which we are going
   to read the values to make proper conversion, and second file is resultant file in which we are storing the values as per need*/



void csvParse(string str1, string str2)
{
    ifstream in(str1);
    ofstream myFile;

    myFile.open(str2, ios::app );

    string line, field;
    int sum=0,row_count=0;

    double cost, GTC,PorL;


    while ( getline(in,line) )    // get next line in file
    {
        sum=0;
        row_count+=1;
        int col_count=0;

        stringstream ss(line);   // it stores one whole line in itself for parsing on the basis of delimiter

        if(row_count!=1)
        {
            myFile<<endl;
        }



        while (getline(ss,field,','))  // break line into comma delimited fields
        {
            col_count+=1;




            if(col_count==1 )         //condition for storing the first column value as it is except of first row header
            {
                if(row_count>1)

                myFile<<field<<", ";

            }



             if(col_count==3)                 // condition for storing the cost value to calculate percentage
            {
                if(row_count>1)
                {
                    cost=atoi(field.c_str());
                }
            }


               if(col_count==4)            // condition for calculating the percentage by using value of cost and Transferred Amount
              {

                if(row_count>1)
                {
                           GTC=atoi(field.c_str());

                    if(cost<GTC)
                    {
                           PorL=((GTC-cost)/cost)*100;

                           myFile<<to_string(PorL)<<", ";
                    }
                    else
                        if(cost>=GTC)
                    {
                           PorL=((cost-GTC)/cost)*100;

                           myFile<<"-"<<to_string(PorL)<<", ";
                    }


                }
            }



              if (col_count==4)          //Condition to acquire 4th column as it is except of first row value
             {
                 if(row_count>1)

                 myFile<<field<<", ";

             }



           if(col_count==5 || col_count==6|| col_count==7) //condition to calculate the sum of last three column as Total Market Place charge
             {
                      sum=sum+atoi(field.c_str());

                if(col_count==7 && row_count!=0)
             {
                       myFile<<sum<<", ";
             }


             }

          }

      }

}




/* Main driver function which basically calls the 'header(string)' function once because in resultant csv file we want header to get add
   in start and only once, and the it calls 'csvParse(string , string)' function for first input file, and again for second input file. Result of both
   gets appended in resultant file one after another */



 int main()
{

    string input0="result.csv"; // Name of resultant file , it should be in same folder, or it gets created if not exist
    header(input0);

    string input1="paymentsheet1.csv"; // First input file , should be in the same folder
    string input2="paymentsheet2.csv"; // Second input file , should be in the same folder

    csvParse(input1, input0);
    csvParse(input2, input0);          // format of the input payment sheet file should be same for each input value.

    return 0;
}
