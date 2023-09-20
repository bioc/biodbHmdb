#include "EntryMaker.hpp"
#include <stdexcept>
#include <iostream>

EntryMaker::EntryMaker() :
    accession_tag("<accession>", "</accession>"),
    closed(true), found_accession(false) {
}

void EntryMaker::openEntry() {
    
    // Current entry not closed
    if ( ! this->closed)
        throw std::runtime_error("Opening a new entry while the current one is" 
                " not closed");
    this->closed = false;
}

void EntryMaker::write(const std::string& s) {

    for (size_t i = 0 ; i < s.length() ; ++i)
        this->write(s[i]);
}

void EntryMaker::write(char c) {

    // Search for accession number
    if ( ! this->accession_tag.isOnStopTag())
        this->search_for_accession(c);
    
    // Write
    this->do_write(c);
}

void EntryMaker::search_for_accession(char nextChar) {

    // Advance
    this->accession_tag.advance(nextChar);
    
    // Inside tag
    if (this->accession_tag.isInside())
        this->current_accession += nextChar;

    // On stop tag
    if (this->accession_tag.isOnStopTag()) {

        // Search backward for first `<`
        size_t inf_index = this->current_accession.rfind('<');
        
        // Extract accession
        this->current_accession = this->current_accession.substr(1,
                inf_index - 1);
        
        // Found accession
        this->found_accession = true;
    }
}

void EntryMaker::closeEntry() {

    if (this->closed)
        throw std::runtime_error("Closing an already closed entry.");
    if ( ! this->found_accession)
        throw std::runtime_error("Closing an entry that has no accession"
                " number.");
    this->do_close_entry();
    this->accessions.push_back(this->current_accession);
    this->current_accession.clear();
    this->found_accession = false;
    this->accession_tag.reset();
    this->closed = true;
}

size_t EntryMaker::getNbEntries() const {
    return this->accessions.size();
}

std::string EntryMaker::getAccession(size_t i) const {
    return this->accessions.at(i);
}

std::vector<std::string> EntryMaker::getAccessions() const {
    return this->accessions;
}
