#include "TagDetector.hpp"
#include <string.h>

TagDetector::TagDetector(const char* start, const char* stop) {
    this->start = start;
    this->stop = stop;
    this->start_end = start + strlen(start) - 1;
    this->stop_end = stop + strlen(stop) - 1;
    this->reset();
}

void TagDetector::reset() {
    this->p = this->start;
    this->inside = false;
    this->is_on_start_tag = false;
    this->is_on_stop_tag = false;
}

bool TagDetector::isInside() const {
    return this->inside;
}

bool TagDetector::isOnStartTag() const {
    return this->is_on_start_tag;
}

bool TagDetector::isOnStopTag() const {
    return this->is_on_stop_tag;
}

std::string TagDetector::getStartTag() const {
    return std::string(this->start);
}

void TagDetector::advance(char c) {

    this->is_on_start_tag = false;
    this->is_on_stop_tag = false;

    // Look for entry start tag
    if ( ! this->inside) {
        if (c == *this->p) {
            if (this->p == this->start_end) {
                this->is_on_start_tag = true;
                this->inside = true;
                this->p = this->stop;
            }
            else
                ++this->p;
        }
        else
            this->p = this->start;
    }

    // Look for entry end tag
    else {
        if (c == *this->p) {
            if (this->p == this->stop_end) {
                this->is_on_stop_tag = true;
                this->inside = false;
                this->p = this->start;
            }
            else
                ++this->p;
        }
        else
            this->p = this->stop;
    }
}
