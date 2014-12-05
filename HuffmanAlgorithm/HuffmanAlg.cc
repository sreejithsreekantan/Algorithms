 /*
    Author      :   Sreejith Sreekantan
    Date        :   May 2014
    Description :   Simplex algorithm is for linear programming 
*/

#include <string>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <functional>
#include <sstream>
#include "HuffmanAlg.hh"

using namespace std;

// template<typename T>
// class lessOrEqual{
//  bool operator()(const T& first, const T& second) {
//      return first->frequency() <= second->frequency();
//  }
// };

struct  NodePtrGreater // : public std::binary_function<HuffmanTreeNode *, HuffmanTreeNode *, bool>
{
    bool operator()(const HuffmanTreeNode *lhs, const HuffmanTreeNode *rhs)
    {
        // clog << lhs->character() << " and " << rhs->character() << " : " << (lhs->frequency() < rhs->frequency()) << endl;
        return lhs->frequency() > rhs->frequency();
    }
};

// bool HuffmanTreeNode::operator<(const HuffmanTreeNode* rhs)
// {
//  clog << character() << " and " << rhs->character() << " : " << (frequency()<rhs->frequency()) << endl;
//  return frequency()<rhs->frequency();
// }

void HuffmanAlg::calcHuffmanCodeRecursive(string encodedText, const HuffmanAlg::Node *const tmp)
{
    // clog << "encodedText : " << encodedText << endl;
    // clog << "left : " << tmp->left() << "right : " << tmp->right() << endl;
    if (tmp->isLeaf())
    {
        code_[tmp->character()] = encodedText;
        return;
    }
    calcHuffmanCodeRecursive(encodedText + "0", tmp->left());
    calcHuffmanCodeRecursive(encodedText + "1", tmp->right());
}

bool HuffmanAlg::solve()
{
    typedef unordered_map<char, Node *> NodeMapType;
    NodeMapType nodeMap;
    for (std::string::iterator i = input_.begin(); i != input_.end(); ++i)
    {
        Node *&iNode = nodeMap[*i];
        if (iNode == NULL)
        {
            iNode = new Node(*i, 1, NULL, NULL);
        }
        else
        {
            iNode->addToFreq();
        }
    }

    // // print out contents of map
    // for (NodeMapType::iterator i = nodeMap.begin(); i != nodeMap.end(); ++i)
    // {
    //     cout << (*i).first  << ".." << (*i).second->frequency() << " isLeaf:" << (*i).second->isLeaf() << endl;
    // }

    typedef priority_queue<Node *, std::vector<Node *>, NodePtrGreater> NodePQType;
    NodePQType nodePQ;
    for (NodeMapType::iterator i = nodeMap.begin(); i != nodeMap.end(); ++i)
    {
        nodePQ.push((*i).second);
    }

    // // print out contents of priority queue
    // NodePQType nodePQtmp;
    // while (!nodePQ.empty())
    // {
    //     cout << nodePQ.top()->character()  << " " << nodePQ.top()->frequency() << " " << nodePQ.top() << endl;
    //      nodePQtmp.push(nodePQ.top());
    //     nodePQ.pop();
    // }
    // while (!nodePQtmp.empty())
    // {
    //  nodePQ.push(nodePQtmp.top());
    //     nodePQtmp.pop();
    // }

    Node *tmp1, *tmp2, *tmp3;
    while (1 < nodePQ.size())
    {
        tmp1 = nodePQ.top(); nodePQ.pop();
        tmp2 = nodePQ.top(); nodePQ.pop();

        tmp3 = new Node('?', (tmp1->frequency() + tmp2->frequency()), tmp1, tmp2);
        // clog << "tmp1 : " << tmp1 << "tmp2 : " << tmp2 << "tmp3 : " << tmp3 << endl;
        // clog << "left : " << tmp3->left() << "right : " << tmp3->right() << endl;
        nodePQ.push(tmp3);
    }

    root_ = nodePQ.top();
    nodePQ.pop(); // just to empty the priority queue to avoid any unexpected behaviour

    code_.clear(); // flush out any previous data
    calcHuffmanCodeRecursive("", root_);

    return true;
}

string HuffmanAlg::code()
{
    ostringstream out;
    for (unordered_map<char, string>::iterator i = code_.begin(); i != code_.end(); ++i)
    {
        out << (*i).first  << ".." << (*i).second << endl;
    }
    return out.str();
}


string HuffmanAlg::encodedText()
{
    ostringstream out;
    // out << "Encoded Text : ";
    for (std::string::iterator i = input_.begin(); i != input_.end(); ++i)
    {
        out << code_[*i];
    }
    out << endl;
    return out.str();
}

string HuffmanAlg::input()
{
    ostringstream out;
    out << input_ << endl;
    return out.str();
}


void HuffmanAlg::decode(ostringstream &out, string::iterator encodedInputIter, const Node *const treePosition)
{
    // clog << endl << "*encodedInputIter : " << *encodedInputIter ;
    
    const Node *tmp = treePosition;
    if (treePosition->isLeaf())
    {
        // clog << " leaf.. ";
        tmp = root_;
        out << treePosition->character();
        // clog << treePosition->character();
    }
    if (*encodedInputIter == '0')
    {
        // clog << " left ";
        tmp = tmp->left();
    }
    else  if (*encodedInputIter == '1')
    {
        // clog << " right ";
        tmp = tmp->right();
    }
    else
    {
        // clog << "not 0 or 1.. : " << *encodedInputIter << endl;
        return;
    }

    decode(out, ++encodedInputIter, tmp);
}

// void HuffmanAlg::decode(ostringstream &out, string::iterator encodedInputIter, const Node *const treePosition)
// {
//     clog << endl << "*encodedInputIter : " << *encodedInputIter ;
//     const Node *tmp;
//     if (*encodedInputIter == '0')
//     {
//         clog << " left ";
//         if (treePosition->left()->isLeaf())
//         {
//             clog << " leaf.. ";
//             if (treePosition->left()->character() == *encodedInputIter)
//             {
//                 tmp = root_;
//                 out << treePosition->left()->character();
//                 clog << treePosition->left()->character();
//             }
//             else
//             {
//                 out << "error in input!!!"  << endl;
//                 return;
//             }
//         }
//         else
//         {
//          tmp = treePosition->left();
//         }
//     }
//     else if (*encodedInputIter == '1')
//     {
//         clog << " right ";
//         if (treePosition->right()->isLeaf())
//         {
//             clog << " leaf.. ";
//             if (treePosition->right()->character() == *encodedInputIter)
//             {
//                 tmp = root_;
//                 out << treePosition->right()->character();
//                 clog << treePosition->right()->character();
//             }
//             else
//             {
//                 out << "error in input!!!"  << endl;
//                 return;
//             }
//         }
//         else
//         {
//          tmp = treePosition->right();
//         }
//     }
//     else
//     {
//         clog << "not 0 or 1.. : " << *encodedInputIter << endl;
//         return;
//     }


//     decode(out, ++encodedInputIter, tmp);
// }
string HuffmanAlg::decode(string encodedText)
{
    ostringstream out;
    out << "Decoded Text : ";
    decode(out, encodedText.begin(), root_);
    out << endl;
    return out.str();
}