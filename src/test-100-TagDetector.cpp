/*
 * This file uses the Catch unit testing library, alongside
 * testthat's simple bindings, to test a C++ function.
 *
 * For your own packages, ensure that your test files are
 * placed within the `src/` folder, and that you include
 * `LinkingTo: testthat` within your DESCRIPTION file.
 */

#include <testthat.h>
#include <Rcpp.h>
#include "TagDetector.hpp"

context("Test TagDetector class") {

    test_that("We can construct a TagDetector object") {

        TagDetector t("<a>", "</a>");
        expect_false(t.isInside());
        expect_false(t.isOnStartTag());
        expect_false(t.isOnStopTag());
    }

    test_that("TagDetector object detects a start and a stop") {
        TagDetector t("<a>", "</a>");
        std::string s("<a></a>");
        for (int i = 0 ; i < 3 ; ++i) {
            expect_false(t.isInside());
            expect_false(t.isOnStartTag());
            expect_false(t.isOnStopTag());
            t.advance(s[i]);
        }
        expect_true(t.isInside());
        expect_true(t.isOnStartTag());
        expect_false(t.isOnStopTag());
        for (int i = 3 ; i < 6 ; ++i) {
            t.advance(s[i]);
            expect_true(t.isInside());
            expect_false(t.isOnStartTag());
            expect_false(t.isOnStopTag());
        }
        t.advance(s[6]);
        expect_false(t.isInside());
        expect_false(t.isOnStartTag());
        expect_true(t.isOnStopTag());
    }
}
