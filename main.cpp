#include <iostream>
#include <string>

using namespace std;

void capitalize(string &word);
void decode(string key);
void encode(string key);
void createTable(char table[5][5], string key);
void insertZLetters (string &word);

int main()
{
    char optionMode = ' ';
    string key;


    cout<<"Provide a key word: "<<endl;
    cin>>key;
    //capitalize all key letters (also changes J letters to I if found)
    capitalize(key);

    //until valid option is selected
    while(1){
        cout<<"Decoding or Encoding mode?(d/e) "<<endl;
        cin >> optionMode;

        if(optionMode=='d' || optionMode=='D'){
            decode(key);
            break;
        }
        else if(optionMode=='e' || optionMode=='E'){
            encode(key);
            break;
        }
    }
    return 0;
}

void capitalize(string &word)
{
    for(int i=0; i<word.length(); i++){
        word[i]=toupper(word[i]);
        if(word[i]=='J')
            word[i]='I';
    }
}

void decode(string key)
{
    string result ="";

    //the table of letters is used to encode or decode word
    char lettersTable[5][5];

    //table created from the key and the alphabet
    createTable(lettersTable, key);

    string word;
    cout<<"Provide a word to decode: "<<endl;
    cin>>word;
    //capitalize all word letters (also changes J letters to I if found)
    capitalize(word);

    //loop checks 2 letters each from the word,
    //decodes them, and adds them to the result
    for (int i=0; i<word.length(); i+=2){

            //coordinates for first and second letter in the table
            int x1, y1, x2, y2;
            bool firstLetterFound=0, secondLetterFound=0;
            //loops to find the coordinates of 2 letters
            for (int y=0; y<5; y++){
                for(int x=0; x<5; x++){
                    if(word[i]==lettersTable[y][x]){
                        x1=x;
                        y1=y;
                        firstLetterFound=true;
                    }
                    else if(word[i+1] == lettersTable[y][x]){
                        x2=x;
                        y2=y;
                        secondLetterFound=true;
                    }
                    if(firstLetterFound && secondLetterFound)
                        break;
                }
            }

            //if both letters are not in the same row or column
            if(x1!=x2 && y1!=y2){
                int temp = x1;
                x1=x2;
                x2=temp;
            }

            //if both letters are in the same column
            else if (x1==x2){
                y1--;
                y2--;
                if(y1==-1)
                    y1=4;
                if(y2==-1)
                    y2=4;
            }

            //if both letters are in the same row
            else if (y1==y2){
                x1--;
                x2--;
                if(x1==-1)
                    x1=4;
                if(x2==-1)
                    x2=4;
            }

            result=result + lettersTable[y1][x1] + lettersTable[y2][x2];

    }
    cout<<"The decoded word is: "<<result<<endl;

}

void encode(string key)
{
    string result ="";

    //the table of letters is used to encode or decode word
    char lettersTable[5][5];

    //table created from the key and the alphabet
    createTable(lettersTable, key);

    string word;
    cout<<"Provide a word to encode: "<<endl;
    cin>>word;
    //capitalize all word letters (also changes J letters to I if found)
    capitalize(word);

    //to encode z letters are added where same letters are next to each other
    //or if the amount of letters is not even
    insertZLetters(word);

    //loop checks 2 letters each from the word,
    //encodes them, and adds them to the result
    for (int i=0; i<word.length(); i+=2){

            //coordinates for first and second letter in the table
            int x1, y1, x2, y2;
            bool firstLetterFound=0, secondLetterFound=0;
            //loops to find the coordinates of 2 letters
            for (int y=0; y<5; y++){
                for(int x=0; x<5; x++){
                    if(word[i]==lettersTable[y][x]){
                        x1=x;
                        y1=y;
                        firstLetterFound=true;
                    }
                    else if(word[i+1] == lettersTable[y][x]){
                        x2=x;
                        y2=y;
                        secondLetterFound=true;
                    }
                    if(firstLetterFound && secondLetterFound)
                        break;
                }
            }

            //if both letters are not in the same row or column
            if(x1!=x2 && y1!=y2){
                int temp = x1;
                x1=x2;
                x2=temp;
            }

            //if both letters are in the same column
            else if (x1==x2){
                y1++;
                y2++;
                if(y1==5)
                    y1=0;
                if(y2==5)
                    y2=0;
            }

            //if both letters are in the same row
            else if (y1==y2){
                x1++;
                x2++;
                if(x1==5)
                    x1=0;
                if(x2==5)
                    x2=0;
            }

            result=result + lettersTable[y1][x1] + lettersTable[y2][x2];

    }
    cout<<"The decoded word is: "<<result<<endl;


}

//function to create table from the keyword
//the table is used to encode or decode word
void createTable(char table[5][5], string key)
{
    //table can be created only of these characters
    char alphabet[25] = {'A', 'B', 'C', 'D', 'E',
                         'F', 'G', 'H', 'I', 'K',
                         'L', 'M', 'N', 'O', 'P',
                         'R', 'Q', 'S', 'T', 'U',
                         'V', 'W', 'X', 'Y', 'Z'};

    //boolean to check if letter from the key word was already used
    bool letterUsed=1;


    //loop to create the table for coding the word

    //going through all rows
    for(int i=0,wordIndex=0; i<5; i++){
        //going through all columns
        for(int j=0; j<5; j++){
            //while key word letters are still not all checked
            while (wordIndex<key.length()){
                //goes through alphabet
                for(int k=0; k<25; k++){
                    if (key[wordIndex]==alphabet[k]){
                        letterUsed = 0;
                        //when letter used, it is changed to 0 in the alphabet array
                        alphabet[k] = '0';
                        break;
                    }
                }
                //if the letter of the key was not used before, assign it to the table
                if(!letterUsed){
                    table[i][j] = key[wordIndex];
                    letterUsed = 1;
                    break;
                }
                //go to the next word letter
                wordIndex++;
            }
            //if all key letters already checked, use letters left from the alphabet to fill the table
            if(wordIndex>=key.length()){
                for (int k=0; k<25; k++){
                        if(alphabet[k]!='0'){
                        table[i][j]=alphabet[k];
                        alphabet[k]='0';
                        break;
                    }
                }
            }
        }
    }
}

void insertZLetters (string &word)
{
    for (int i=0; i<word.length(); i++){
        //if 2 letters same next to each other, insert Z in between
        if(word[i-1]==word[i]){
            word.insert(i, "Z");
        }
    }
}
