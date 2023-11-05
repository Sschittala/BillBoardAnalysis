// Program 4: Billboard analysis
// create a C++ program that will quantify and summarize Billboard chart data. The dataset covers the top 50 songs from "The Hot 100" charts over the time period of 1960-2020, and is broken up into three different files by time period. Your program will have options to analyze this data in different ways.
// Course: CS 141, Spring 2022
// System: Macbook OS, Macbook OS
// Author: Sai Chittala

#include <iostream> // for input and output
#include <fstream>  // for opening files
#include <string>   // for checking strings
#include <vector>  // for vectors
#include <cassert>
#include <algorithm>
using namespace std;
//-------------------------
// class stores file data
class RecentMusic 
{
  public:
     string date;
     int rank;
     string song;
     string artist;
     int last_week;
     int peak_rank;
     int weeks_on_board;
     RecentMusic(){date="";rank=0;song="";last_week=0;peak_rank=0;weeks_on_board=0;}    
};
//--------------------------------------
//Reads a csv file into a class vector
void readWordsIntoDictionary( vector <RecentMusic> & dictionary,string file_name)
{
  // Read in dictionary into dictionary vector
   ifstream inStream;    // Declare an input stream for reading
   inStream.open(file_name); // Open dictionary file
   assert( inStream.fail() == false );  // Ensure file open worked
  
   dictionary.clear();
  
   string newWord="";
   int count = 0; 
   int comma;
   int comma2;
   int len;
   bool start = true;
   RecentMusic musicData;                       // Store a single input word
   while(getline(inStream,newWord)) {
      if(start == false)
      {
        comma = newWord.find(',');
        comma2 = newWord.find(',',comma+1);
        len = comma2 - comma;
        musicData.date = newWord.substr(0,comma);        // While there is another word to be read
        musicData.rank = stoi(newWord.substr(comma+1,len-1));
        comma = newWord.find(',',comma+1);
        comma2 = newWord.find(',',comma+1);
        len = comma2 - comma;
        musicData.song = newWord.substr(comma+1,len-1);
        comma = newWord.find(',',comma+1);
        comma2 = newWord.find(',',comma+1);
        len = comma2 - comma;
        musicData.artist = newWord.substr(comma+1,len-1);
        comma = newWord.find(',',comma+1);
        comma2 = newWord.find(',',comma+1);
        len = comma2 - comma;
        if(len>1){musicData.last_week = stoi(newWord.substr(comma+1,len-1));}
        comma = newWord.find(',',comma+1);
        comma2 = newWord.find(',',comma+1);
        len = comma2 - comma;
       if(len>1){musicData.peak_rank = stoi(newWord.substr(comma+1,len-1));}
       comma = newWord.find(',',comma+1);
       len = newWord.size() - comma;
       if(len>1){musicData.weeks_on_board = stoi(newWord.substr(comma+1,len-1));}
       dictionary.push_back(musicData);
      }
      start = false;
   }
 
   // Close the dictionary file
   inStream.close();
}
//---------------------------------
// Different file option choices
void fileOption(int &fOption) 
{
  cout<<"This program will analyze weekly Billboard data spanning from 1960 - 2020.\n"<<endl;
  cout<<"Select file option:\n"
  <<"   1. To analyze charts top 50: 1960 - 1980 data file\n"
  <<"   2. To analyze charts top 50: 1981 - 2000 data file\n"
  <<"   3. To analyze charts top 50: 2001 - 2020 data file\n"
  <<"Your choice --> ";
  cin>>fOption;
}
//--------------------------------------------------------
// Different menu options for the user to choose from.
void menuOption(int &mOption) 
{
  do
  {
  cout<<endl<<"\nSelect a menu option: \n"
  <<"   1. Display overall information about the data\n"
  <<"   2. Display the Billboard info of the song with the most #1 occurrences for a given decade or year\n"
  <<"   3. Display the Billboard info for the most long-lasting song on the charts for a given decade or year\n"
  <<"   4. Display the Billboard info for the song with the greatest weekly climb on the charts given a decade or year\n"
  <<"   5. Artist Search - Return the Billboard info for records that matches user input for artist search\n"
  <<"   6. Exit\n"
  <<"Your choice --> ";
  cin>>mOption;
  if((mOption>6)||(mOption<1)) // checks if the user chooses a number greater than 6 or less than 1
  {
     cout<<endl<<"Invalid value.  Please re-enter a value from the menu options below.";
  }
  }while((mOption>6)||(mOption<1));
}
//----------------------------------------------
// displays overall information about the data
void menuOption1(vector<RecentMusic> chart) 
{
 vector<string> indivSongs;
 
 for(int i = 0; i<chart.size();i++)
 {
    if((count(indivSongs.begin(),indivSongs.end(),chart[i].song))==0)
    {
       indivSongs.push_back(chart[i].song);
    }
 }
 for(int i =0;i<indivSongs.size();i++)
 {
 
 }
  cout<<"\nTotal number of rows: "<<chart.size()<<endl;
  cout<<"Number of unique songs represented in the dataset: "<<indivSongs.size()<<endl; 
}
//-----------------------------------------------------------------
// Puts the songs from a user selected year/decade into a vector
void decadeOrYear(vector<RecentMusic> chart,char choice,int year,vector<RecentMusic> &decade_year) 
{
   int lastSlash;
   int currYear;
   for(int i =0;i<chart.size();i++)
     {
        lastSlash = chart[i].date.find('/',3);
        currYear = stoi(chart[i].date.substr(lastSlash+1,4));
        if(choice == 'D')
        {
           if((currYear<=(year+9))&&(currYear>=year))
           {
              decade_year.push_back(chart[i]);
           }
        }
        else
        {
           if(currYear==year)
           {
              decade_year.push_back(chart[i]);
           }
        }
     }
}
//-------------------------------------------------------------------------------------------------
// Display the Billboard info of the song(s) with the most #1 occurrences for a given decade or year
void menuOption2Choice(vector<RecentMusic> chart,char choice,int year)
{
  int currYear;
  int temp = 0;
  string song;
  vector<RecentMusic> decade_year;
  vector<string> number1;
  vector<string> bestNumber1;
  vector<string> artists;
  vector<string> bestArtists;
  decadeOrYear(chart,choice,year,decade_year);
     for(int i = 0;i<decade_year.size();i++)
     {
        if(decade_year[i].rank==1)
        {
           number1.push_back(decade_year[i].song);
           artists.push_back(decade_year[i].artist);
        }
     }
     for(int i =0;i<number1.size();i++)
     {      
        if((count(number1.begin(),number1.end(),number1[i]))>temp)
        {
           temp = count(number1.begin(),number1.end(),number1[i]);
        }
     }
     for(int i =0;i<number1.size();i++)
     {
        if((count(bestNumber1.begin(),bestNumber1.end(),number1[i])==0))
        {
           if((count(number1.begin(),number1.end(),number1[i]))==temp)
           {
              bestNumber1.push_back(number1[i]);
              bestArtists.push_back(artists[i]);
           }
        }
     }
     cout<<"\n\nThe song(s) with the most #1 occurrences for selected time period is: "<<endl;
     for(int i = 0;i<bestNumber1.size();i++)
     {
        for(int j =0;j<decade_year.size();j++)
        {
           if((bestNumber1[i]==decade_year[j].song))
           {
              cout<<"Song Title: "<<decade_year[j].song<<endl;
              cout<<"Artist: "<<bestArtists[i]<<endl;
              cout<<"# of occurrences: "<<temp<<endl;
              cout<<"\n"<<endl;
              break;
           }
        }
     }
}
//--------------------------------------------------------------------------------------------------------
// Displays the Billboard info for the song with the highest number of weeks for a given decade or year.
void menuOption3Choice(vector<RecentMusic> chart,char choice,int year) 
{
  int currYear;
  int temp = 0;
  string song;
  string artist;
  vector<RecentMusic> decade_year;
  decadeOrYear(chart,choice,year,decade_year);
  for(int i = 0;i<decade_year.size();i++)
  {
        if(decade_year[i].weeks_on_board>temp)
        {
           temp = decade_year[i].weeks_on_board;
           song = decade_year[i].song;
           artist = decade_year[i].artist;
        }
  }
  cout<<"The song with the highest number of weeks on the charts is: "<<endl;
  cout<<"\t"<<song<<" by "<<artist<<" with "<<temp<<" weeks on the chart."<<endl;
 
}
//------------------------------------------------------------------------------------------------------------------
// Displays the Billboard info for the song with the greatest weekly climb on the charts given a decade or year.
void menuOption4Choice(vector<RecentMusic> chart,char choice,int year)
{
  int currYear;
  int temp = 0;
  string song;
  string artist;
  vector<RecentMusic> decade_year;
  vector<RecentMusic> highestClimbs;
  decadeOrYear(chart,choice,year,decade_year);
  for(int i = 0;i<decade_year.size();i++)
  {
        if((decade_year[i].last_week-decade_year[i].rank)>temp)
        {
           temp = decade_year[i].last_week-decade_year[i].rank;
        }
  }
  for(int i = 0;i<decade_year.size();i++)
  {
        if((decade_year[i].last_week-decade_year[i].rank)==temp)
        {
          highestClimbs.push_back(decade_year[i]);
        }
  }
  cout<<"\nThe song(s) with the greatest climb from previous week to current week position: "<<endl;
  for(int i =0;i<highestClimbs.size();i++)
  {
     cout<<"        Song Title: "<<highestClimbs[i].song<<endl;
     cout<<"         Artist: "<<highestClimbs[i].artist<<endl;
     cout<<"         Week of: "<<highestClimbs[i].date<<endl;
     cout<<"         Previous Week Position: "<<highestClimbs[i].last_week<<endl;
     cout<<"         Current Week Position: "<<highestClimbs[i].rank<<endl;
     cout<<"         Difference of "<<(highestClimbs[i].last_week-highestClimbs[i].rank)<<" between previous week and current week position"<<endl;
  }
}
//------------------------------------------------------------------------------------------------------
// Artist Search - Retrieves the first 10 or less records of #1 songs that match by artist name
void menuOption5(vector<RecentMusic> chart) 
{
  vector<string> normalArtist;
  string artist;
  vector<string> artists;
  vector<RecentMusic> artistBest;
  int found;
  cout<<"Enter search text to retrieve first 10 records of #1 songs that match by artist name: "<<endl;
  cin.ignore();
  getline(cin,artist);
  for(int i = 0;i<artist.size();i++)
  {
     artist[i]=toupper(artist[i]);
  }
  for(int i = 0; i<chart.size();i++)
  {
     normalArtist.push_back(chart[i].artist);
     for(int j = 0;j<chart[i].artist.size();j++)
     {
        chart[i].artist[j] = toupper(chart[i].artist[j]);
     }
     artists.push_back(chart[i].artist);
     chart[i].artist = normalArtist[i];
     found=artists[i].find(artist);
      if((found>=0)&&(chart[i].rank==1))
      {
         artistBest.push_back(chart[i]);
      }
  }
  if(artistBest.size()==0)
  {
     cout<<"No matching artists were found."<<endl;
     return;
  }
  cout<<"Retrieval of first 10 #1 records found based upon search by artist name: "<<endl;
  for(int i = 0;i<artistBest.size();i++)
  {
     if(i<10)
     {
     cout<<i+1<<") Song: "<<artistBest[i].song<<endl;
     cout<<"     Artist: "<<artistBest[i].artist<<endl;
     cout<<"     Week of: "<<artistBest[i].date<<endl;
     cout<<"     Week Position: "<<artistBest[i].rank<<endl;
     }
     else /// exits the program
     {
        return;
     }
 
  }
 
 
}
//------------------------------------------------------------------------------------
//Function puts users choice of decade or year in the menuOption functions parameters
void menuOptionChoices(vector<RecentMusic> chart,int choice)
{
  int year;
  char timeFrame;
  int lastSlash = chart[0].date.find('/',3);
  int lastYear = stoi(chart[0].date.substr(lastSlash+1,4));
  lastSlash = chart[chart.size()-1].date.find('/',3);
  int firstYear = stoi(chart[chart.size()-1].date.substr(lastSlash+1,4));
  cout<<"Enter D to select a decade or Y to select a year."<<endl;
  cout<<"Your choice --> ";
  cin>>timeFrame;
  while((toupper(timeFrame)!='D')&&(toupper(timeFrame)!='Y'))
  {
     cout<<"Invalid entry. Try again."<<endl;
     cout<<"Enter D to select a decade or Y to select a year."<<endl;
     cout<<"Your choice --> ";
     cin>>timeFrame;
  }
  if(toupper(timeFrame)=='D')
  {
     cout<<"Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)."<<endl;
     cin>>year;
     year = year-year%10;
     if((year<firstYear-1)||(year>lastYear))
     {
        cout<<"No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen."<<endl;
        return;
     }
     if(choice==2)
     {
        menuOption2Choice(chart,'D',year);
     }
     if(choice==3)
     {
        menuOption3Choice(chart,'D',year);
     }
     if(choice==4)
     {
        menuOption4Choice(chart,'D',year);
     }
  }
  else if(toupper(timeFrame)=='Y')
  {
     cout<<"Enter the year you would like to choose (e.g. 2001)."<<endl;
     cin>>year;
     if((year<firstYear)||(year>lastYear))
     {
        cout<<"No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen."<<endl;
        return;
     }
     if(choice==2)
     {
        menuOption2Choice(chart,'Y',year);
     }
     if(choice==3)
     {
        menuOption3Choice(chart,'Y',year);
     }
     if(choice==4)
     {
        menuOption4Choice(chart,'Y',year);
     }
  }
}
//-------------------------------------------------------------
//Excutes the program through using the different functions
int main() {
  cout<<"Program 4: BillBoard Analysis "<<endl;
  cout<<"CS 141, Spring 2022, UIC "<<endl;
  cout<<" "<<endl;
  int fOption;
  int mOption;
  vector<RecentMusic> dictionary1960; 
  vector<RecentMusic> dictionary1981;
  vector<RecentMusic> dictionary2001;
  vector<RecentMusic> dictionaryChoice;
  // calling different vectors
 
  readWordsIntoDictionary(dictionary1960,"charts_top50_1960_1980.csv"); // calling the function to read the data for the first file
  readWordsIntoDictionary(dictionary1981,"charts_top50_1981_2000.csv"); // calling the function to read the data for the second file
  readWordsIntoDictionary(dictionary2001,"charts_top50_2001_2020.csv");
// calling the function to read the data for the third file
fileOption(fOption); // calling this function to help user pick a file option from the choices
if((fOption>3)||(fOption<1)) // if user enters a number greater than 3 or less than 1, it prints out invalid value.
{
     cout<<"\nInvalid value. Exiting Program.";
     return 0;
  }
  if(fOption == 1) // if user enters 1, data reads from the first file option
  {
     dictionaryChoice = dictionary1960;
  }
  else if(fOption == 2) // if user enters 2, data reads from the second file option
  {
     dictionaryChoice = dictionary1981;
  }
  else // // if user enters 3, data reads from the third file option
  {
     dictionaryChoice = dictionary2001;
  }
  menuOption(mOption);
  while(mOption!=6) 
  {
     if(mOption == 1)
     {
        menuOption1(dictionaryChoice);
     }
     else if(mOption==2)
     {
        menuOptionChoices(dictionaryChoice,2);
     }
     else if(mOption==3)
     {
        menuOptionChoices(dictionaryChoice,3);
     }
     else if(mOption==4)
     {
        menuOptionChoices(dictionaryChoice,4);
     }
     else if(mOption==5)
     {
        menuOption5(dictionaryChoice);
     }
     menuOption(mOption);
  }
 
  return 0;
}
