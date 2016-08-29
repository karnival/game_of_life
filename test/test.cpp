#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cell.hpp>

TEST_CASE( "cells can be killed and restored", "[cell]" ) {
    Cell a;
    Cell b(true);
    Cell c(false);

    SECTION( "cells initialised properly" ) {
        REQUIRE(!a.is_alive());
        REQUIRE(b.is_alive());
        REQUIRE(!c.is_alive());
    }

    SECTION( "cells can change their alive/dead state" ) {
        a.live();
        b.die();
        c.live();
        REQUIRE(a.is_alive());
        REQUIRE(!b.is_alive());
        REQUIRE(c.is_alive());
    }
}
