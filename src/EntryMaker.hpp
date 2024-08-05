#ifndef _ENTRY_MAKER_H
#define _ENTRY_MAKER_H
#include <string>
#include <vector>
#include "TagDetector.hpp"

class EntryMaker {
    public:
        EntryMaker();
        void openEntry();
        void write(const std::string&);
        void write(char);
        void closeEntry();
        size_t getNbEntries() const;
        std::string getAccession(size_t) const;
        std::vector<std::string> getAccessions() const;
        bool isParsingEntry() const { return ! this->closed; }
        
    protected:
        virtual void do_write(char) = 0;
        virtual void do_close_entry() = 0;
        TagDetector accession_tag;
        bool closed;
        std::string current_accession;
        std::vector<std::string> accessions;
        bool found_accession;
        void search_for_accession(char);
};
#endif
