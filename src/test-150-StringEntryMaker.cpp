#include <testthat.h>
#include <Rcpp.h>
#include "StringEntryMaker.hpp"
#include <iostream>

context("Test StringEntryMaker class") {
    
    test_that("We can create an instance") {
        StringEntryMaker em;
        expect_true(em.getNbEntries() == 0);
    }

    test_that("We can create one entry") {
        StringEntryMaker em;
        em.openEntry();
        std::string accession = "HMDB0001";
        std::string entry = "<metabolite><accession>" + accession
            + "</accession></metabolite>";
        em.write(entry);
        em.closeEntry();
        expect_true(em.getNbEntries() == 1);
        expect_true(em.getEntry(0) == entry);
        expect_true(em.getAccession(0) == accession);
    }

    test_that("We can create two entries") {
        StringEntryMaker em;
        em.openEntry();
        std::string entry1 = "<metabolite><accession>A"
            "</accession></metabolite>";
        std::string entry2 = "<metabolite><accession>B"
            "</accession></metabolite>";
        em.write(entry1);
        em.closeEntry();
        expect_true(em.getNbEntries() == 1);
        expect_true(em.getEntry(0) == entry1);
        em.openEntry();
        em.write(entry2);
        em.closeEntry();
        expect_true(em.getNbEntries() == 2);
        expect_true(em.getEntry(0) == entry1);
        expect_true(em.getEntry(1) == entry2);
    }
}
