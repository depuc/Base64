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

std::string encode_base64(std::vector<char> data){

    std::string encoded;
    int val = 0;
    int valb = -6;

    for(unsigned char c : data){
        
        val = (val << 8) + c;
        valb += 8;

        while(valb>=0){
            int index = (val >> valb) & 0x3F;
            encoded += base64[index];
            valb -= 6;}
    }

    if (valb > - 6){
        int index = ((val << 8) >> (valb + 8)) & 0x3F;
        encoded += base64[index];
    }

    while(encoded.size() % 4){
        encoded += '=';
    }

    return encoded;
}

void Write_File_In_Base64(std::string& filename, std::string& Base64Text){
   
    std::ofstream file(filename,std::ios::trunc);
    
    if(!file){
        std::cerr<<"Error: writing to file\n" ;
        return;
    }

    file << Base64Text;
    file.close();
}

std::string Read_And_Encode_Base64(const std:: string filename){
    
    std::vector<char> data = read_file(filename);
    
    if(data.empty()) return "";
    return encode_base64(data);    
}

int main(int argc, char* argv[]){
   
    init_base64_index_table();
    
    if (argc < 3) {
            std::cerr << "Usage:\n"
                      << "./run -f <filename>         # Overwrite file with Base64\n"
                      << "./run -f <infile> <outfile> # Encode infile to outfile\n"
                      << "./run -c <filename>         # Print Base64 to stdout\n";
            return 1;
    }

    std::string mode = argv[1];

    if(mode == "-f" && argc == 3){
        std::string filename = argv[2];
        std::string encoded = Read_And_Encode_Base64(filename);
        if(encoded.empty()) return 1;
        Write_File_In_Base64(filename,encoded);
        std::cout<<"Overwritten "<<filename<<" with base64 content.\n";
    }
    else if(mode == "-c" && argc == 3){
        std::string filename = argv[2];
        std::string encoded = Read_And_Encode_Base64(filename);
        if(encoded.empty()) return 1;
        std::cout<<encoded<<'\n';
    }
    else if(mode == "-f" && argc == 4){
        
        std::string infile  = argv[2];
        std::string outfile = argv[3];
        std::string encoded = Read_And_Encode_Base64(infile);
        if(encoded.empty()) return 1;
        Write_File_In_Base64(outfile,encoded);
        std::cout<<"Written "<< outfile <<" with base64 content.\n";
    }
    else {
        std::cerr << "Invalid arguments.\n";
        return 1;
    }
    return 0;
}

