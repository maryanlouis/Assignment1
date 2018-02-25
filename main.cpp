#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//function to compare two string and generate front compressed string
string compStr(string strPr,string strCur){
    int counter=0;
    while( counter < strPr.size() && counter < strCur.size() ){
        if(strCur[counter]== strPr[counter])
            counter++;
        else break;
    }
    if(counter==0)
        return strCur;
    return (char)(counter+'0')+strCur.substr(counter);
}

string compNum(string numl){
    int index=0,decimalVal;
    string compNum;
    while(index<numl.size()-1){
        decimalVal=(numl[index]-'0')*10+(numl[index+1]-'0');
        if(decimalVal==10)
            decimalVal=100;
        compNum =compNum+(char)decimalVal;
        index=index+2;
    }
    if(index==numl.size()-1)
        compNum=compNum+'}'+numl[index];

    return compNum;
}

void compressFun(){

    string line,prevname,name,number; //lines get from files

    ifstream idBook("idbook.txt");   //input file
    ofstream idBookcomp("idbookcomp.txt"); //output file

    if(idBook.is_open() && idBookcomp.is_open()){
            //get first line from input file
            //write it as it is in output file
        getline(idBook,line);

        name=line.substr(0,line.find("\t"));
        number=line.substr(line.find("\t")+1);
        cout<<name<<"\t"<<number<<endl;
        idBookcomp << name+"\t";
        idBookcomp << compNum(number)+"\n";
        prevname=name;
  //repeat but compare previous string with current string until end of file
       while(getline(idBook,line)){
            name=line.substr(0,line.find("\t"));
            number=line.substr(line.find("\t")+1);
            cout<<name<<number<<endl;
            idBookcomp << compStr(prevname,name)+"\t";
            idBookcomp << compNum(number)+"\n";
            cout<<prevname<<"\t"<<compNum(number)<<endl;
            prevname=name;
        }
        idBookcomp.close();
        idBook.close();
    }
    else
        cout<<"can't open file"<<endl;
}





string decompStr(string strPr,string strCur){
    if(strCur[0]<='9'){
    int counter=strCur[0]-'0';
    string dename=strPr.substr(0,counter);
    return dename+strCur.substr(1);
    }
    else    return strCur;
}

string decompNum(string compnum){
    int index=0,decimalVal;
    char chr1,chr2;
    string decompNum;

    while(index<compnum.size()){
        decimalVal=compnum[index];
        if(decimalVal==100)
            decimalVal=10;
        chr1=(decimalVal/10)+'0';
        chr2=(decimalVal%10)+'0';
        decompNum=decompNum+chr1+chr2;
        index++;
        if(index==compnum.size()-2)
            if(compnum[index]=='}')
                return decompNum+compnum[index+1];
    }

    return decompNum;
}

void decompressFun(){

    string line,prevname,name,number; //lines get from files

    ifstream idBookcomp("idbookcomp.txt");   //input file
    ofstream idBookdecomp("idbookdecomp.txt"); //output file

    if(idBookdecomp.is_open() && idBookcomp.is_open()){
            //get first line from input file
            //write it as it is in output file
        getline(idBookcomp,line);

        name=line.substr(0,line.find("\t"));
        number=line.substr(line.find("\t")+1);
        cout<<name<<"\t"<<decompNum(number)<<endl;
        idBookdecomp << name+"\t";
        idBookdecomp << decompNum(number)+"\n";
        prevname=name;
  //repeat but compare previous string with current string until end of file
       while(getline(idBookcomp,line)){
            name=line.substr(0,line.find("\t"));
            number=line.substr(line.find("\t")+1);
           // cout<<name<<"\t"<<number<<endl;
            idBookdecomp << decompStr(prevname,name)+"\t";
            idBookdecomp << decompNum(number)+"\n";
            cout<<decompStr(prevname,name)<<"\t"<<decompNum(number)<<endl;
            prevname=decompStr(prevname,name);
        }
        idBookcomp.close();
        idBookdecomp.close();

    }
    else
        cout<<"can't open file"<<endl;
}


int main()
{
    compressFun();
    decompressFun();

    return 0;
}
