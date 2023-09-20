#ifndef _TAG_DETECTOR_H
#define _TAG_DETECTOR_H
#include <string>

class TagDetector {

    public:
        TagDetector(const char* start, const char* stop);

        void reset();

        bool isInside() const;

        bool isOnStartTag() const;

        bool isOnStopTag() const;

        void advance(char c);
        
        std::string getStartTag() const;
    
    private:
        const char* start;
        const char* stop;
        const char* start_end;
        const char* stop_end;
        const char* p;
        bool inside;
        bool is_on_start_tag;
        bool is_on_stop_tag;
};
#endif
