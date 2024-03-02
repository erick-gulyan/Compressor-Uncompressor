#include <iostream>
#include "Helper.hpp"
#include "HCTree.hpp"
#include <vector>
using namespace std;

int main(int argc, char* argv[]){
    
    if(argc !=3){
        cerr << "ERROR: Incorrect Number of Arguments" << endl; 
        exit(1);
    }
    FancyInputStream istream  (argv[1]);
    if(istream.filesize() == 0){
        FancyOutputStream ostream (argv[2]);
        return 0;
    }
    vector<int> freq (256,0);
    int idx;
    while((idx = istream.read_byte())!=-1){
        //stores counts in freq
        
        freq[idx] = freq[idx] +1;
        
    }
    cout<<"Freq size"<<freq.size()<<endl;
    cout<<"Ran Line "<<__LINE__<<endl;
    HCTree tree = HCTree();
    tree.build(freq);
    cout<<"Ran Line "<<__LINE__<<endl;
    //freq vector
    // for(unsigned int i=0;i<freq.size();i++){
        
    // }
    FancyOutputStream ostream (argv[2]);

    // //Header part of ofstream

    /*EFFICIENT HEADER DESIGN: STORE counts
    as 3 byte values, since max count is 10 million.
    cieling log 2 of (10million) = 24bits = 3 bytes
    3 bytes > 4 for space  

    Modified READ/WRITE_INT to read size(int)-1 
    bytes. So, 3 bytes.  
    */
    
    if(ostream.good()){
        for(unsigned int i=0;i<freq.size();i++){
            
            ostream.write_int(freq[i]);
            // cout<<freq[i]<<" ";
        }
    }
    cout<<"Ran Line "<<__LINE__<<endl;
    istream.reset();
    int symb;
    // ostream.flush_bitwise();
    while((symb = istream.read_byte()) !=-1){
        tree.encode((unsigned char)symb, ostream);
        
    }
    cout<<"Ran Line "<<__LINE__<<endl;
    
}
