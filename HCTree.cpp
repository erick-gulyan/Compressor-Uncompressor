#include "HCTree.hpp"
#include <stack>
#include <algorithm>

void HCTree::build(const vector<int>& freqs){
    //use vector of counts to build tree
     //const vector, so use a new list
    //first 2 elements  will be two new nodes connected with their parent = 
    
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
    for(unsigned int i=0;i<freqs.size();i++){ 
        if(freqs[i] != 0){
            HCNode* newNode = new HCNode(freqs[i], i);
            leaves[i] = newNode;
            pq.push(newNode);
        }
        
    }

    
    //for all nonzero counts, create 2 nodes with 2 lowest 
    //counts and make parent node to connect them together
    //add those nodes to vector leaves at
    //position int(node->symbol)
    while(pq.size() >=2){
           HCNode* node0 = pq.top();
           pq.pop();
           HCNode* node1 = pq.top();
           pq.pop();
            //store char of left child as char for parent    
           HCNode* parent = new HCNode
           ((node0->count)+(node1->count), node0->symbol);
           pq.push(parent);
           //puts parent in pq so now we can compare its counts
           parent->c0 = node0;
           parent->c1 = node1;
           node0->p = parent;
           node1->p = parent;
        }
    if(pq.size() !=0){
        this->root = pq.top();
    }
}

// void HCTree::printTree(HCNode* node){
//     vector<int> edgelist;
//     if(node == nullptr){
//         return;
//     }
//     cout<<node->symbol<<" / "<<node->count<<endl;
//     if(node->c0 !=nullptr){
//         cout<<"Edges: c0 = "<<node->c0->count;
//     }
//     else{
//         cout<<"Edges: c0 = nullptr";
//     }
//     if(node->c1 !=nullptr){
//         cout<<" c1= "<<node->c1->count<<endl;
//     }
//     else{
//         cout<<"/ c1 = nullptr"<<endl;
//     }
//     printTree(node->c0);
//     printTree(node->c1);
// }


void HCTree::encode(unsigned char symbol, FancyOutputStream & out) const{
/*
Start at leave node of symbol. Move up parent
Check if moving up as node0 or node1, and append 0/1
to the stack

Then, our encoding is the bit string we pop off stack
*/
    HCNode * node = leaves[symbol];
    stack<int> bitstring;
    if(this->root == nullptr){
        return;
    }
    unsigned char ch;
    while(node != this->root){
        if(node->p !=nullptr){
            ch = node->symbol;
            node = node->p;
            if(node->c0->symbol == ch){
                bitstring.push(0);
            }
            if(node->c1->symbol == ch){
                bitstring.push(1);
            }
            
        }
    }
    while(!bitstring.empty()){
        out.write_bit(bitstring.top());
        bitstring.pop();
        
    }
}

/*
Given input stream, decode message
*/
unsigned char HCTree::decode(FancyInputStream & in) const {
    HCNode* curNode = this->root;
    //while input has no bit flags(eofbit, badbit, etc)
    while(in.good()){
        //
        if(curNode->c0 == nullptr && curNode->c1 == nullptr){
            //leaf node found
            return curNode->symbol;
        }
        //read bit, if 0, move to c0
        //if 1, move to c1 and continue traversal until leaf
        bool bit = in.read_bit();

        if(bit == 0){
            curNode = curNode->c0;
        }
        else{
            curNode = curNode->c1;
        }
    }
    return 0x00; //null
    
}

HCTree::~HCTree(){
    recursiveClear(this->root);
}

void HCTree::recursiveClear(HCNode * node){
    if(node == nullptr){
        return;
    }       
    recursiveClear(node->c0);
    recursiveClear(node->c1);
    
    
    // if(node->p != nullptr && node== node->p->c0){
    //     node->p->c0 = nullptr;
    // }
    // if(node->p != nullptr && node== node->p->c1){
    //     node->p->c1 = nullptr;
    // }
    // node->p = nullptr;
    delete node;
}
