#include <iostream>
#include <unordered_map>
#include <fstream>
#include <queue>
#include <string>
#include<sys/time.h>
#include "omp.h"

using namespace std;

struct timeval t1, t2, t3, t4, t5;

typedef unsigned long long ticks;

struct HuffmanNode{
int count;
char character;
HuffmanNode* left;
HuffmanNode* right;
//Constructor set 
HuffmanNode(char x, int y, HuffmanNode* l, HuffmanNode* r): count(y), character(x), left(l), right(r){}
HuffmanNode(char x, int y): count(y), character(x), left(NULL), right(NULL){}
HuffmanNode(): left(NULL), right(NULL){}
};
//Function Object 
struct CompareFunction {
    bool operator()(HuffmanNode *a, HuffmanNode * b)
    {
        return a->count > b->count;
    }
};

//Function Declarations (defined below Main)
int ReadInputFile(unordered_map<char,int> &Global);
int PerfromConversion();
int BuildHuffmanTree();
int TraverseHuffmanTree(HuffmanNode * root, string bits, int place);
bool LeafNode(HuffmanNode * Node);
void EncodeFile();

//Global Variables
string filename;
unordered_map<char,int> GlobalDictionary;
priority_queue< HuffmanNode*, vector<HuffmanNode*>, CompareFunction> GlobalQueue;
HuffmanNode *root;
unordered_map<char,string> EncodingHolder;

int main (int argc, char * argv[]){
    if(argc <2){
        cout << "Usage: HuffmanCoding.x InputFile.txt" <<endl;
        exit(0);
    }
    gettimeofday(&t1, NULL);
    filename = argv[1];
    fstream inputFile(filename);
    //may need to change method of finding file size
    inputFile.seekg (0, inputFile.end);
    int length = inputFile.tellg();
    cout << "Number of Bytes in Input File: " << length <<endl;
    inputFile.seekg (0, inputFile.beg);
    ReadInputFile(GlobalDictionary);
    gettimeofday(&t3, NULL);
    PerfromConversion();
    BuildHuffmanTree();
    string temp;
    TraverseHuffmanTree(root,temp,0);
//print outs 
// for ( auto itr = EncodingHolder.begin(); itr != EncodingHolder.end(); itr++){
 // cout << itr ->first << " " <<  itr->second <<endl;
  //}
    gettimeofday(&t4, NULL);
    EncodeFile();
    gettimeofday(&t2, NULL);
            cout << "Total Time: " <<endl;
            printf("%d milliseconds\n",
	       (t2.tv_sec - t1.tv_sec)*1000 + 
	       (t2.tv_usec - t1.tv_usec) / 1000);
           cout << "Time to Read Input File and populate HashTable: " <<endl;
           printf("%d milliseconds\n",
	       (t3.tv_sec - t1.tv_sec)*1000 + 
	       (t3.tv_usec - t1.tv_usec) / 1000);
           cout << "Time to Encode file: " <<endl;
           printf("%d milliseconds\n",
	       (t2.tv_sec - t4.tv_sec)*1000 + 
	       (t2.tv_usec - t4.tv_usec) / 1000);
             cout << "Time to perform Huffman Algorithm: " <<endl;
            printf("%d milliseconds\n",
	       (t4.tv_sec - t3.tv_sec)*1000 + 
	       (t4.tv_usec - t3.tv_usec) / 1000);

}

int ReadInputFile(unordered_map<char,int> &Global){
string temp;
unordered_map<char,int> LocalDictionary;
fstream inputFile(filename);
char c;
    while(inputFile.get(c)){
        LocalDictionary[c]++;
    }
    Global = LocalDictionary;
}

//Newline character and spaces are read in differently
int PerfromConversion(){
  auto itr = GlobalDictionary.begin();
  for (int i=0; i < GlobalDictionary.size(); i++){
  //cout << itr ->first << " " <<  itr->second <<endl;
  HuffmanNode *temp = new HuffmanNode(itr->first, itr->second);
  GlobalQueue.push(temp);
  itr++;
  }
  //for(int i=0; i < 10; i++){
   // cout << GlobalQueue.top().character <<endl;
  //  GlobalQueue.pop();
 // }
}


int BuildHuffmanTree(){
while(GlobalQueue.size() >1){
HuffmanNode *temp1 = GlobalQueue.top();
GlobalQueue.pop();
HuffmanNode *temp2 = GlobalQueue.top();
GlobalQueue.pop();
//Create a HuffmanNode via struct constructor 
HuffmanNode *temp3 = new HuffmanNode('$', temp1->count+temp2->count, temp1, temp2) ;
GlobalQueue.push(temp3);
}
    root = GlobalQueue.top();
   /* HuffmanNode *T = root;
 
        cout << T->character <<endl;
        T = T->right;
        cout << T->character <<endl; 
         T = T->right;
        cout << T->character <<endl;
     
     
    if(LeafNode(T)){
        cout <<"HIT" <<endl;
    }*/
    
}

int TraverseHuffmanTree(HuffmanNode * root, string bits, int place){
   // cout << root->character <<endl;
   if (root->left) {
         bits.insert(place,"0");
        TraverseHuffmanTree(root->left, bits, place+1);
    }
  
    if (root->right) {
        bits.insert(place,"1");
        TraverseHuffmanTree(root->right, bits, place+1);
    }
  
   if (LeafNode(root)) {
     //  cout << root->character <<endl;
       string temp;
       for(int i =0; i < place; i++){
           temp.push_back(bits[i]);
          // cout << bits[i];
       }
      // cout << temp;
        EncodingHolder[root->character] = temp;
       temp.clear();
      
    }
}

bool LeafNode(HuffmanNode * Node){
   if((Node->right == NULL) && (Node->left == NULL) ){
        return true;
    }
    return false;
}


void EncodeFile(){
    fstream inputFile(filename);
    ofstream OutputFile("Encoding.txt");
    char c;
    while(inputFile.get(c)){
        string hold = EncodingHolder[c];
        OutputFile << hold;
    }
    OutputFile.close();
    
}