 /*
    Author      :   Sreejith Sreekantan
    Date        :   May 2014
    Description :   Simplex algorithm is for linear programming 
*/

#ifndef __HUFFMANALG_HH__
#define __HUFFMANALG_HH__

#include <string>
#include <unordered_map>
#include <sstream>
// #include <iostream> 
// using namespace std;
using std::unordered_map;
using std::string;

class HuffmanTreeNode final
{
public:
	HuffmanTreeNode(const char character, const int freq, const HuffmanTreeNode* left=NULL, const HuffmanTreeNode* right=NULL):
		character_(character), freq_(freq), left_(left), right_(right)
	{ 
		// clog << "left : " << left << "right : " << right 
		// 	<< "left_ : " << left_ << "right_ : " << right_  
		// 	<< "character_ : " << character_ << "freq_ : " << freq_ 
		// 	<< endl;
	}
	~HuffmanTreeNode() 
	{
		if (left_)  { delete left_; }
		if (right_) { delete right_; }
	}
	bool isLeaf() const { return (left_==NULL && right_==NULL); }
	char character() const { return character_; }
	void addToFreq(int incr=1) { freq_+=incr; }
	int frequency() const { return freq_; }
	const HuffmanTreeNode * left() const {return left_;}
	const HuffmanTreeNode * right() const {return right_;}
private:
	const char character_;
	int freq_;
	const HuffmanTreeNode * left_;
	const HuffmanTreeNode * right_;
};

class HuffmanAlg
{
public:
	typedef HuffmanTreeNode Node;
	HuffmanAlg(const std::string& input):input_(input), root_(NULL) {}
	~HuffmanAlg() { if(root_) {delete root_;} }
	bool solve();
	string encodedText();
	string code();
	string input();
	string decode(string encodedText);
	
private:
	void calcHuffmanCodeRecursive(string, const HuffmanAlg::Node* const);
	void decode(std::ostringstream& , string::iterator, const Node* const );
	std::string input_;
	Node* root_;
	unordered_map<char, string> code_;

};

#endif	// __HUFFMANALG_HH__
