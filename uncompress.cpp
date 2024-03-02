#include "Helper.hpp"
#include "HCTree.hpp"

int main(int argc, char * argv[]){
    if(argc !=3){
        cerr << "ERROR: Incorrect Number of Arguments" << endl; 
        exit(1);
    }
    FancyInputStream istream (argv[1]);
    vector<int> freq (256,0);
    int cnt = 0;
    //keep count of total number of bytes we need to read
    //so we dont read a byte when were done.
    if(istream.filesize() >0){
        for(int i=0;i<256;i++){
            //read first 256 integers to freq vector.
            freq[i] = istream.read_int();
            if(freq[i]!=0){
                cnt += freq[i];
            }
        }
    }
    HCTree tree;
    tree.build(freq);

    FancyOutputStream ostream(argv[2]);
    int currentByteCount = 0;
    unsigned char ch;
    while(currentByteCount < cnt && istream.good()){
        ch = tree.decode(istream);
        ostream.write_byte(ch);
        ++currentByteCount;
    }
    return 0;
}
