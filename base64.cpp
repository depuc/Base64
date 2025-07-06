#include <iostream>
#include <map>


int main(){
  
    std::map<int,char> base64;
   
    int index = 0;

    for(char c = 'A'; c <= 'Z'; ++c) base64[index++] = c;          
    for(char c = 'a'; c <= 'z'; ++c) base64[index++] = c;          
    for(char c = '0'; c <= '9'; ++c) base64[index++] = c; 
    base64[index++] = '+';
    base64[index++] = '/';
    
    for(std::map<int,char>::iterator it = base64.begin(); it != base64.end(); it++){
        std::cout << "Key: " << it->first <<" Value: " << it->second<<'\n';
    }

    return 0;
}

