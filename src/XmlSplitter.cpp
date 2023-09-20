#include "XmlSplitter.hpp"
#include "EntryMaker.hpp"
#include "TagDetector.hpp"

XmlSplitter::XmlSplitter(EntryMaker* em) {
    this->em = em;
}

void XmlSplitter::parse(std::istream& is) {
    
    TagDetector entry_tag("<metabolite>", "</metabolite>");

    int c;
    while ((c = is.get()) != EOF) {
        
        entry_tag.advance(c);
        
        // Start entry
        if (entry_tag.isOnStartTag()) {
            this->em->openEntry();
            this->em->write(entry_tag.getStartTag());
        }
        
        // End entry
        else if (entry_tag.isOnStopTag()) {
            this->em->write(c);
            this->em->closeEntry();
            entry_tag.reset();
        }
        
        // Inside entry
        else if (entry_tag.isInside())
            this->em->write(c);
    }
    
    if (this->em->isParsingEntry())
        throw std::runtime_error("Input was truncated while parsing an entry.");
}
