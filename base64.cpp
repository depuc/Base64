#include <iostream>
#include <map>
#include <vector>
#include <fstream>
std::map<int,char> base64;

void init_base64_index_table(){
  
   
    int index = 0;

    for(char c = 'A'; c <= 'Z'; ++c) base64[index++] = c;          
    for(char c = 'a'; c <= 'z'; ++c) base64[index++] = c;          
    for(char c = '0'; c <= '9'; ++c) base64[index++] = c; 
    base64[index++] = '+';
    base64[index++] = '/';
    
}

std::vector<char> read_file(const std::string& filename){

    std::ifstream file(filename, std::ios::binary);

    if(!file){
        std::cerr<< "Error: cannot open file" << filename << '\n';
        return {};
    }

    file.seekg(0,std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0,std::ios::beg);

    std::vector<char> buffer(size);

    if(!file.read(buffer.data(),size)){
       std::cerr<< "Error: Failed to read file" << filename <<'\n';  
       return {};
    }

    return buffer;
}



int main(){
   
    init_base64_index_table();
    std::string filename = "README.md";  
    std::vector<char> binaryData = read_file(filename);

    std::cout << "Read " << binaryData.size() << " bytes.\n";

    for (size_t i = 0; i < std::min(binaryData.size(), size_t(10)); ++i) {
        printf("%02X ", static_cast<unsigned char>(binaryData[i]));
    }
    std::cout << std::endl;
}

