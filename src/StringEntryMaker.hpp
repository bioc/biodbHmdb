#ifndef _STRING_ENTRY_MAKER_H
#define _STRING_ENTRY_MAKER_H
#include "EntryMaker.hpp"

class StringEntryMaker : public EntryMaker {
    public:
        StringEntryMaker();
        std::string getEntry(size_t) const;

    protected:
        virtual void do_write(char);
        virtual void do_close_entry();

    private:
        std::vector<std::string> entries;
        std::string current_entry;
};
#endif
