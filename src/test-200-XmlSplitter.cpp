#include <testthat.h>
#include <Rcpp.h>
#include "XmlSplitter.hpp"
#include "StringEntryMaker.hpp"

context("Test XmlSplitter class") {

    test_that("We can parse a single XML entry") {
        std::string entry = "<metabolite><accession>A</accession></metabolite>";
        std::istringstream iss_xml(entry);
        StringEntryMaker em;
        XmlSplitter splitter(&em);
        splitter.parse(iss_xml);
        expect_true(em.getNbEntries() == 1);
        expect_true(em.getEntry(0) == entry);
    }

    test_that("We can extract two entries") {
        std::string entry1 = "<metabolite><accession>A"
            "</accession></metabolite>";
        std::string entry2 = "<metabolite><accession>B"
            "</accession></metabolite>";
        std::istringstream iss_xml(entry1 + entry2);
        StringEntryMaker em;
        XmlSplitter splitter(&em);
        splitter.parse(iss_xml);
        expect_true(em.getNbEntries() == 2);
        expect_true(em.getEntry(0) == entry1);
        expect_true(em.getEntry(1) == entry2);
        expect_true(em.getAccession(0) == "A");
        expect_true(em.getAccession(1) == "B");
    }

    test_that("We fail if input is truncated") {
        std::string entry = "<metabolite><accession>A</accession></metab";
        std::istringstream iss_xml(entry);
        StringEntryMaker em;
        XmlSplitter splitter(&em);
        expect_error(splitter.parse(iss_xml));
    }
}
