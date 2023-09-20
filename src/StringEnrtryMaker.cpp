#include "StringEntryMaker.hpp"
#include <stdexcept>
#include <iostream>

StringEntryMaker::StringEntryMaker() {
}

void StringEntryMaker::do_write(char c) {
    
    // Write
    this->current_entry += c;
}

void StringEntryMaker::do_close_entry() {

    if (this->current_entry.empty())
        throw std::runtime_error("Closing an empty entry.");

    this->entries.push_back(this->current_entry);
    this->current_entry.clear();
}

std::string StringEntryMaker::getEntry(size_t i) const {
    return this->entries.at(i);
}
