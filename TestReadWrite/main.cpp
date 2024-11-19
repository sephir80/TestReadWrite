//
//  main.cpp
//  TestReadWrite
//
//  Created by Alessandro Tognon on 19/11/24.
//

#include <iostream>
#include <format>
#include <fstream>
#include <vector>
#include <string>

using std::string;

const size_t maxstring {1024};
const char * filename("docs/items.txt");
const char tab_char('\t');
char buf[maxstring] {};


class Item {
    int _sku {};
    string _name {};
    string _desc {};
public:
    Item (){ reset();}
    Item (int sku,string & name,string & desc) :_sku(sku),_name(name),_desc(desc) {}
    Item (const Item& rhs);
    Item & operator = (const Item& rhs);
    ~Item(){reset();}
    void reset() {_sku=0;_name=_desc="unk";}
    void sku(int sku){_sku=sku;}
    int sku(){return _sku;}
    void name(const string & name){_name = name;}
    string name () const {return _name;}
    void desc(const string & desc){_desc=desc;}
    string desc() const {return _desc;}
};

Item::Item(const Item& rhs){
    _sku = rhs._sku;
    _name = rhs._name;
    _desc = rhs._desc;
}

Item & Item::operator = (const Item & rhs)
{
    if(this != &rhs)
    {
        _sku = rhs._sku;
        _name = rhs._name;
        _desc = rhs._desc;
    }
    return  *this;
}

std::vector<string> strsplit(const string& s)
{
    std::vector<string> strs_v;
    size_t start_loc {};
    size_t sep_loc {};
    while (true)
    {
        sep_loc = s.find(tab_char,start_loc);
        strs_v.push_back(s.substr(start_loc,sep_loc-start_loc));
        if (sep_loc ==string::npos) break;
        start_loc = sep_loc +1;
    }
    return strs_v;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::ifstream inFile(filename);
    while (inFile.good()) {
        inFile.getline(buf,sizeof(buf));
        if (!*buf) break;
        std::vector<string> split_v {strsplit(buf)};
        
        if (split_v.size()<3) continue;
        
        Item current_item {std::stoi(split_v[0]),split_v[1],split_v[2]};
        std::cout << std::format("sku :{} , NAME: {} , DESC: {}\n",current_item.sku(),current_item.name(),current_item.desc());
    }
    
    
    return 0;
}
