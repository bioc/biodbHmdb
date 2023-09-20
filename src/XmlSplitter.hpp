#include <iostream>

class EntryMaker;

class XmlSplitter {
    
    public:
        XmlSplitter(EntryMaker*);
        
        void parse(std::istream&);
        
    private:
        EntryMaker *em;
};
