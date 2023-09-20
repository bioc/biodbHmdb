#include "FileEntryMaker.hpp"
#include <fstream>
#include <sstream>

FileEntryMaker::FileEntryMaker(const std::string& folder) :
    folder(folder), outf(NULL) {
}

void FileEntryMaker::do_write(char c) {
    
    // Write
    if (this->found_accession) {
        
        // Open file
        if ( ! this->outf) {
            std::ostringstream filename;
            filename << this->folder << "/" << this->current_accession << ".xml";
            std::string entry_filename = filename.str();
            this->outf = new std::ofstream(entry_filename.c_str());
            this->filenames.push_back(entry_filename);
            
            // Write buffer
            *this->outf << this->buffer;
            this->buffer.clear();
        }
        
        // Write
        this->outf->put(c);
    }
    
    // Store character
    else
        this->buffer += c;
}

void FileEntryMaker::do_close_entry() {
    
    // Close file
    if (this->outf) {
        this->outf->close();
        this->outf = NULL;
    }

    this->buffer.clear();
}

std::string FileEntryMaker::getFilename(size_t i) const {
    return this->filenames.at(i);
}
