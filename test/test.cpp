#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

#include <cell.hpp>
#include <grid.hpp>

TEST_CASE( "cells can be killed and restored", "[cell]" ) {
    Cell a;
    Cell b(true);
    Cell c(false);

    SECTION( "cells initialised properly" ) {
        REQUIRE(!a.is_alive());
        REQUIRE(b.is_alive());
        REQUIRE(!c.is_alive());
    }

    SECTION( "cells can change their alive/dead state through live() and die()" ) {
        a.live();
        b.die();
        c.live();
        REQUIRE(a.is_alive());
        REQUIRE(!b.is_alive());
        REQUIRE(c.is_alive());
    }

    SECTION( "cells can also change sate through set_cell_state()" ) {
        a.set_cell_state(true);
        b.set_cell_state(false);
        c.set_cell_state(true);
        REQUIRE(a.is_alive());
        REQUIRE(!b.is_alive());
        REQUIRE(c.is_alive());
    }

}

TEST_CASE( "individual cells update correctly", "[cell]") {
    Cell dead_start(false);
    Cell alive_start(true);

    SECTION( "zero neighbours" ) {
        auto neighbours = std::vector<bool> { false, false, false, false, false, false, false, false };

        REQUIRE(!dead_start.update_cell(neighbours));
        REQUIRE(!alive_start.update_cell(neighbours));
    }

    SECTION( "one neighbour" ) {
        auto neighbours = std::vector<bool> { true , false, false, false, false, false, false, false };

        REQUIRE(!dead_start.update_cell(neighbours));
        REQUIRE(!alive_start.update_cell(neighbours));
    }

    SECTION( "two neighbours" ) {
        auto neighbours = std::vector<bool> { true , true,  false, false, false, false, false, false };

        REQUIRE(!dead_start.update_cell(neighbours));
        REQUIRE(alive_start.update_cell(neighbours));
    }

    SECTION( "three neighbours" ) {
        auto neighbours = std::vector<bool> { true , true,  true, false, false, false, false, false };

        REQUIRE(dead_start.update_cell(neighbours));
        REQUIRE(alive_start.update_cell(neighbours));
    }

    SECTION( "four neighbours" ) {
        auto neighbours = std::vector<bool> { true , true,  true , true , false, false, false, false };

        REQUIRE(!dead_start.update_cell(neighbours));
        REQUIRE(!alive_start.update_cell(neighbours));
    }
}

TEST_CASE( "grids can be created", "[grid]" ) {
    Grid a(10,5);

    REQUIRE(a.num_rows() == 10);
    REQUIRE(a.num_cols() == 5);
}

TEST_CASE( "grid cell-setters and cell-getters work as expected", "[grid]" ) {
    Grid a(1,1);

    a.set_cell_state(0, 0, false);
    REQUIRE(!a.get_cell_state(0, 0));

    a.set_cell_state(0, 0, true);
    REQUIRE(a.get_cell_state(0, 0));
    
    Grid b(2,2);

    b.set_cell_state(1, 1, false);
    REQUIRE(!b.get_cell_state(1, 1));

    b.set_cell_state(1, 0, true);
    REQUIRE(b.get_cell_state(1, 0));
}
