/*
Input and expected output has been provided by the University of Pretoria
*/

#include "../catch/catch.hpp"

#include <iostream>
#include <math.h>

#include "RowsColumns.h"
#include "ZigZag.h"
#include "utils.h"

using namespace std;

/*
    It is unclear how fitchfork is testing this, if testing this at all.
*/
TEST_CASE("RowsColumns Exceptions", "[!mayfail]")
{
    string text="Hello, World!..";

    string longText="Emily Elizabeth Dickinson was an American poet. Dickinson was born in Amherst, Massachusetts. Although part of a prominent family with strong ties to its community, Dickinson lived much of her life highly introverted.";
    string encoded;

    RowsColumns rc;

    bool thrown;
    string msg;
    string decoded = "";

    // As tested in given main.cpp
    try {
      decoded = rc.decode(text);
    } catch (const char * e) {
        thrown = true;
        msg = e;
    }

    REQUIRE(thrown == true);
    REQUIRE(msg == "Incompatible text length");
    REQUIRE(decoded == "");

    thrown = false;
    msg = "";
    decoded = "";

    try {
      decoded = rc.decode(longText);
    } catch (const char * e) {
      thrown = true;
      msg = e;
    }

    REQUIRE(thrown == true);
    REQUIRE(msg == "Incompatible text length");
    REQUIRE(decoded == "");

}

/*
    It is unclear how fitchfork is testing this, if testing this at all.
*/
TEST_CASE("ZigZag Exceptions", "[!mayfail]")
{
    string text="Hello, World!..";

    string longText="Emily Elizabeth Dickinson was an American poet. Dickinson was born in Amherst, Massachusetts. Although part of a prominent family with strong ties to its community, Dickinson lived much of her life highly introverted.";
    string encoded;

    ZigZag zz;

    bool thrown = false;
    string msg = "";
    string decoded = "";

    try {
      decoded = zz.decode(text);
    } catch (const char * e) {
      thrown = true;
      msg = e;
    }

    REQUIRE(thrown == true);
    REQUIRE(msg == "Incompatible text length");
    REQUIRE(decoded == "");

    thrown = false;
    msg = "";
    decoded = "";

    try {
      zz.decode(longText);
    } catch (const char * e) {
        thrown = true;
        msg = e;
    }

    REQUIRE(thrown == true);
    REQUIRE(msg == "Incompatible text length");
    REQUIRE(decoded == "");

}

TEST_CASE("RowColumns encode/decode")
{
    string text="Hello, World!..";

    string longText="Emily Elizabeth Dickinson was an American poet. Dickinson was born in Amherst, Massachusetts. Although part of a prominent family with strong ties to its community, Dickinson lived much of her life highly introverted.";
    string encoded;

    RowsColumns rc;
    encoded = rc.encode(text);
    REQUIRE(encoded == "Hoo!e,r.l l.lWd ");
    REQUIRE(rc.decode(encoded) == "Hello, World!.. ");

    encoded = rc.encode(longText);
    REQUIRE(encoded == string("E atsstrnsiD fvmDn. tsttttimeeii  b,.  ") + \
    "rscu rlcADo  ofo kchtykmirMAfancihie iecnal mgon gdEnrk stai " + \
    "msoh.lsiiish ltmofl iocnnaopyiun y znas cur en h  a noAhgowsilei " + \
    "bw nmuhmi tirn eap hs ittyv t tsoweepnho,elr h eartae   dio ");
    REQUIRE(rc.decode(encoded) == applyPadding(longText));

}

TEST_CASE("ZigZag encode/decode")
{
    string text="Hello, World!..";

    string longText="Emily Elizabeth Dickinson was an American poet. Dickinson was born in Amherst, Massachusetts. Although part of a prominent family with strong ties to its community, Dickinson lived much of her life highly introverted.";
    string encoded;

    ZigZag zz;
    encoded = zz.encode(text);
    REQUIRE(encoded == "Hoo!.r,el l. dWl");
    REQUIRE(zz.decode(encoded) == applyPadding(text));

    encoded = zz.encode(longText);
    REQUIRE(encoded == "E atsstrnsiD fveemittttst .nDmii  b,.  rscu rthck ofo  oDAclykmirMAfancihiedg nogm lancei Enrk stai msoh. lfomtl hsiiisliocnnaopyiun y   h ne ruc sanza noAhgowsilei  nrit imhumn wbeap hs ittyv t  rle,ohnpeewosth eartae   dio ");
    REQUIRE(zz.decode(encoded) == applyPadding(longText));

}
