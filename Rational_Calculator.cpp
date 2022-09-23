/*
 * Program Name: Rational Number Calculator .cpp
 * Program Description: Calculator with Rational number  
 * Last Modification Date: 21/03/2022
*/

#include<bits/stdc++.h>
#include <regex>
#include<algorithm>
#include<vector>
using namespace std;

/*
 * Function takes Numinator and Deniminator make them in Fraction form.
 * Check if both of them divisible by 2,3 or 5
*/
void simplify(int finalNuminator, int finalDeniminator){
    while(true){
        if(finalNuminator % 2 == 0 && finalDeniminator % 2 == 0){
            finalNuminator /= 2;
            finalDeniminator /= 2;
        }
        else if(finalNuminator % 3 == 0 && finalDeniminator % 3 == 0){
            finalNuminator /= 3;
            finalDeniminator /= 3;
        }
        else if(finalNuminator % 5 == 0 && finalDeniminator % 5 == 0){
            finalNuminator /= 5;
            finalDeniminator /= 5;
        }else{break;}
    }
    cout << "= ";
    cout << finalNuminator <<"/" << finalDeniminator << endl;
}


int main (){
    
    string equ; int option;
    bool isZenDen = false, isValid = true;
    int num, numNeg;   
    while(true){
        cout << "\n--------------------------\n"
                "\nWelcome to Rational Number Calculator.\n"
                "What do you like to do today?\n"
                "1- Enter equation.\n"
                "2- Exit.\n";
        cout << "Choose an option: ";
        cin >> option;
        cin.ignore();
        if(option == 1){
        cout <<"Enter an equation:\n";
        getline(cin,equ);
        equ.erase(remove(equ.begin(),equ.end(),' '),equ.end());

        // Check for Zero division error
        for(int i = 0; i < equ.length(); i++){
            if(equ[i] == '/'){
                if(equ[i+1] == '0')
                    isZenDen = true;
                    isValid = false;
            }
        }
        // Check that input has no characters.
        if(isZenDen == false){
        regex equRE("[+-]?[0-9]+([*/+-]?[+-]?[0-9]+)*");
        isValid = regex_match(equ,equRE);

        if (isValid == true){
            vector < pair <int,int> > number;
            vector <char> operation; 
            number.push_back({0,0});
            string numStr; int previousOpr = 0 ,currentOpr;

            /*
            * Put each term in Vector pair with (0,0) Between each one.
            * Search for operators then Substring text befor it 
            * Check if wheather it is negative or in the deniminator
            */
            for(int i = 0; i < equ.length(); i++){
                switch(equ[i]){
                    case '+':
                        currentOpr = i;

                        operation.push_back(equ[i]);

                        numStr = equ.substr(previousOpr, currentOpr);
                    
                        num = stoi(numStr);
                        if(equ[previousOpr - 1] == '-')
                            numNeg =  -num;
                        else
                            numNeg = num;  

                        if(equ[previousOpr - 1] == '/')
                            number.push_back({1, numNeg});
                        else    
                            number.push_back({numNeg,1});

                        previousOpr = currentOpr + 1;
                        numStr = "";
                        number.push_back({0,0});
                        break;

                    case '-':
                        currentOpr = i;
    
                        if(previousOpr  == currentOpr){
                            break;
                        }
                        operation.push_back(equ[i]);

                        numStr = equ.substr(previousOpr, currentOpr);
                        
                        num = stoi(numStr);
                        
                        if(equ[previousOpr - 1] == '-')
                            numNeg =  -num;
                        else
                            numNeg = num;

                        if(equ[previousOpr - 1] == '/')
                            number.push_back({1, numNeg});
                        else    
                            number.push_back({numNeg,1}); 

                        previousOpr = currentOpr + 1;
                        numStr = "";
                        number.push_back({0,0});
                        break;

                    case '*':
                        currentOpr = i;

                        operation.push_back(equ[i]);
                        
                        numStr = equ.substr(previousOpr, currentOpr);

                        num = stoi(numStr);
                        if(equ[previousOpr - 1] == '-')
                            numNeg =  -num;
                        else
                            numNeg = num;

                        if(equ[previousOpr - 1] == '/')
                            number.push_back({1, numNeg});
                        else    
                            number.push_back({numNeg,1});                    
                        previousOpr = currentOpr + 1;
                        numStr = "";                    
                        break;
                    case '/':
                        currentOpr = i;

                        operation.push_back(equ[i]);  

                        numStr = equ.substr(previousOpr, currentOpr);
            
                        num = stoi(numStr);
                        if(equ[previousOpr - 1] == '-')
                            numNeg =  -num;
                        else
                            numNeg = num;

                        if(equ[previousOpr - 1] == '/')
                            number.push_back({1, numNeg});
                        else    
                            number.push_back({numNeg,1});
                        previousOpr = currentOpr + 1;
                        numStr = "";                       
                        break;
                }
            } 
            numStr = equ.substr(currentOpr+1, equ.length());
            num = stoi(numStr);
                
                if(equ[currentOpr] == '-')
                    numNeg =  -num;
                else
                    numNeg = num;

                if(equ[currentOpr] == '/')
                    number.push_back({1, numNeg});
                else    
                    number.push_back({numNeg,1});
                previousOpr = currentOpr + 1;        
            number.push_back({0,0});
    
            /*
            * Calculate each term and put in fraction vector
            * Check if term is free or have multiplication or division operators
            */
            int sumMinus = 0, previousZero = 0, currentZero;
            int numinator = 1, deniminator = 1;
            int FinalNuminator = 1, FinalDeniminator = 1;
            vector < pair <int,int> > fraction; 
            for(int i = 1; i < number.size(); i++){
                if(number[i].first == 0 && number[i].second == 0){
                    currentZero = i;
                    if( (currentZero - previousZero) <= 2){
                        sumMinus += number[i-1].first;
                        
                    }
                    else{
                        while(previousZero < (currentZero-1)){
                            numinator *= number[previousZero + 1].first;
                            deniminator *= number[previousZero + 1].second;
                            previousZero += 1;
                        }
                            fraction.push_back({numinator,deniminator});

                        if(deniminator == 1){
                            FinalNuminator += numinator;
                        }
                        else{
                            FinalNuminator = FinalNuminator * deniminator + numinator;
                            FinalDeniminator *= deniminator;
                        }
                            numinator = 1;
                            deniminator = 1;
                    }
                    
                    previousZero = currentZero;
                }
            }
            FinalNuminator -= 1;

            // Count number of each operator 
            int countMultiply = 0, countDivide = 0;
            int countPlus = 0, countMinus = 0;
            int count;
            bool divideConseqience = false;
            for(int i = 0; i < operation.size(); i++){
                if(operation[i] == '/'){
                    if(operation[i+1] == '/'){
                        divideConseqience = true;
                    }
                }
                switch(operation[i]){
                    case '*':
                        countMultiply += 1;
                        break;
                    case '/':
                        countDivide += 1;
                        break;
                    case '+':
                        countPlus += 1;
                        break;
                    case '-':
                        countMinus += 1;
                        break; 
                }
            }
            count = countMultiply + countDivide;

            
            fraction.push_back({sumMinus,1});
            int len = fraction.size(); 
            if(countMultiply == countDivide || countDivide == 0 || countMultiply == 0)
                len = fraction.size() - 1;
            
            if (count % 2 == 1)
                count += 1;
            
            while (count != 2 && count > 2 && count % 2 == 0){
                len += 2;
                count -= 2;
            }
            
            if(countMultiply == countDivide + 1 || countDivide == countMultiply + 1)
                len -= 2;

            if(divideConseqience == true && countDivide != 2)
                len -= 2;
            if(divideConseqience == true && countDivide == 2)
                len -= 1;
            // Collect numbers in Fraction vector
            int upper = 0, lower = 0, a,b,c,d;
                for(int i = 0; i <= len ; i+=2){
                    a = fraction[i].first;
                    b = fraction[i].second;
                    c = fraction[i+1].first;
                    d = fraction[i+1].second;
                    upper = a*d + b*c;
                    lower = b*d;
                    fraction.push_back({upper,lower});
                }
            /*
            for(auto i = fraction.begin(); i != fraction.end(); i++){
                cout << i->first << "  " << i->second << endl;
            } 
        */
            
            bool allPlusMinus = false;
            for(int i = 0; i < operation.size(); i++){
                if(operation[i] == '+' || operation[i] == '-'){
            
                    allPlusMinus = true;
                }
                else{
                    allPlusMinus = false;
                    break;
                }
            } 
            if(allPlusMinus == false){
                simplify(fraction[fraction.size()-1].first,fraction[fraction.size()-1].second);
            }
            else{
                simplify(fraction[fraction.size()-2].first,fraction[fraction.size()-2].second);
            }
        }
            else{
                cout << "Ivalid input. Try again.";
            }    
        }
        else{
            cout << "Zero Division error.";
        }
    }
    else{
        break;
    }
}
    return 0;
}