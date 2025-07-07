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
    // Open the file
    std::ifstream file(filename, std::ios::binary);

    if(!file){
        std::cerr<< "Error: cannot open file" << filename << '\n';
        return {};
    }
    // Find the File Size
    file.seekg(0,std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0,std::ios::beg);

    std::vector<char> buffer(size);

    //copy binaries to buffer
    if(!file.read(buffer.data(),size)){
       std::cerr<< "Error: Failed to read file" << filename <<'\n';  
       return {};
    }

    return buffer;
}

std::vector<char> encoded_base64(std::vector<char> data){

    std::string encoded;
    int val = 0;
    int valb = -6;

    for(unsigned char c : data){
        
        val = (val << 8) + c;
        valb += 8;

    }
    
    while(valb>=0){
        int index = (val >> valb) & 0x3F;
        encoded += base64[index];
        valb -= 6;
    }

    if (valb > - 6){
        int index = ((val << 8) >> (valb + 8)) & 0x3F;
        encoded += base64[index];
    }

    while(encode.size() % 4){
        encoded += '=';
    }

    return encoded;
}





int main(){
   
    init_base64_index_table();
   
    std::string filename;

    std::cin >> filename;
    //std::string filename = "README.md";  
    
    std::vector<char> binaryData = read_file(filename);

    std::cout << "Read " << binaryData.size() << " bytes.\n";

    for (size_t i = 0; i < std::min(binaryData.size(), size_t(10)); ++i) {
        printf("%02X ", static_cast<unsigned char>(binaryData[i]));
    }
    std::cout << std::endl;
}

