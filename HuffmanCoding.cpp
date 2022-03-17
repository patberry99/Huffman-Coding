#include <iostream>
#include <unordered_map>
#include <fstream>
#include <queue>

using namespace std;

//Function Declarations (defined below Main)
int ReadInputFile(unordered_map<char,int> &Global);
int PerfromConversion();
int BuildHuffmanTree();

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

//Global Variables
string filename;
unordered_map<char,int> GlobalDictionary;
priority_queue< HuffmanNode*, vector<HuffmanNode*>, CompareFunction> GlobalQueue;
HuffmanNode *root;

int main (int argc, char * argv[]){
    if(argc <2){
        cout << "Usage: HuffmanCoding.x InputFile.txt" <<endl;
        exit(0);
    }
    filename = argv[1];
    fstream inputFile(filename);
    //may need to change method of finding file size
    inputFile.seekg (0, inputFile.end);
    int length = inputFile.tellg();
    cout << length <<endl;
    inputFile.seekg (0, inputFile.beg);
    ReadInputFile(GlobalDictionary);
    PerfromConversion();
    BuildHuffmanTree();
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
 // cout << itr ->first << " " <<  itr->second <<endl;
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
    HuffmanNode *T = root;
    for (int i=0; i < 10;i++){
        cout << T->character <<endl;
        T = T->left;
    }
    
    
}