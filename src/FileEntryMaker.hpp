#ifndef _FILE_ENTRY_MAKER_H
#define _FILE_ENTRY_MAKER_H
#include "EntryMaker.hpp"

class FileEntryMaker : public EntryMaker {
    public:
        FileEntryMaker(const std::string&);
        std::string getFilename(size_t) const;

    protected:
        virtual void do_write(char);
        virtual void do_close_entry();

    private:
        std::string folder;
        std::string buffer;
        std::ofstream *outf;
        std::vector<std::string> filenames;
};
#endif
