#include <Rcpp.h>
#include <fstream>
#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//#include <zip.h>
#include "XmlSplitter.hpp"
#include "FileEntryMaker.hpp"

// ' Extract entries from HMDB XML database file.
// '
// ' The input XML file is read entirely and each entry (e.g.: '<metabolite>'
// element) is extracted and written in a separate file inside the destination
// folder.
// '
// ' @param xmlFile Path of the HMDB XML database file.
// ' @param extractDir Path of the folder where to extract entries.
// ' @return A character vector containing the paths to the extracted entries.
// ' Names are set to the entry accessions.
// '
// ' @export
// [[Rcpp::export]]
Rcpp::StringVector extractXmlEntries(const std::string& file,
                                     const std::string& extractDir) {

    Rcpp::StringVector entryFiles;

    // Check destination folder exists
    struct stat info;
    if (stat(extractDir.c_str(), &info) != 0 || ! (info.st_mode & S_IFDIR))
        Rcpp::stop("Destination folder \"%s\" does not exist.",
                extractDir.c_str());

    // Read input file character by character
    try {
        
        FileEntryMaker em(extractDir);
        XmlSplitter splitter(&em);
        
        // Detect file type
        size_t dot_index = file.rfind('.');
        std::string ext = file.substr(dot_index + 1);

        // Parse XML file
        if (ext == "xml") {

            // Open XML file
            std::ifstream inf(file.c_str());

            // Check XML file exists
            if ( ! inf.good())
                throw std::runtime_error("XML file does not exist.");

            splitter.parse(inf);

            // Close XML file
            inf.close();
        }

        // Unknown extension
        else {
            throw std::runtime_error("Does not know how to handle file type "
                    + ext + " with " + file + ".");
//            int err = 0;
//            zip_t *z = zip_open(file.c_str(), 0, &err);
//            if ( ! z)
//                throw std::runtime_error("Error while opening ZIP file "
//                        + file);
//            if (zip_close(z))
//                throw std::runtime_error("Error when closing ZIP file " + file);
        }

        // Fill vector of filenames
        for (size_t i = 0 ; i < em.getNbEntries() ; ++i)
            entryFiles.push_back(em.getFilename(i));
        entryFiles.attr("names") = em.getAccessions();

    } catch (std::exception& e) {
        Rcpp::stop(e.what());
    }

    return entryFiles;
}
