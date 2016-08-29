#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

#include <cell.hpp>
#include <grid.hpp>
#include <util.hpp>

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

TEST_CASE( "grid equality comparison works as expected", "[grid]") {
    Grid a(2,2);
    Grid b(2,2);
    Grid c(2,2);

    a.set_cell_state(0, 0, false);
    a.set_cell_state(0, 1, true);
    a.set_cell_state(1, 0, true);
    a.set_cell_state(1, 1, false);

    b.set_cell_state(0, 0, false);
    b.set_cell_state(0, 1, true);
    b.set_cell_state(1, 0, true);
    b.set_cell_state(1, 1, false);

    c.set_cell_state(0, 0, true);
    c.set_cell_state(0, 1, true);
    c.set_cell_state(1, 0, true);
    c.set_cell_state(1, 1, false);

    REQUIRE(a == b);
    REQUIRE(a != c);
}

TEST_CASE( "grids permit looking up cell neighbours", "[grid]") {
    Grid a(3,3);

    a.set_cell_state(0, 0, false);
    a.set_cell_state(0, 1, true );
    a.set_cell_state(0, 2, false);
    a.set_cell_state(1, 0, true );
    a.set_cell_state(1, 1, false);
    a.set_cell_state(1, 2, true );
    a.set_cell_state(2, 0, false);
    a.set_cell_state(2, 1, true );
    a.set_cell_state(2, 2, false);

    SECTION( "middle cell's neighbours" ) {
        auto neighbours = a.get_neighbours_state(1, 1);
        auto expected_neighbours = std::vector<bool>( {0, 1, 0, 1, 1, 0, 1, 0} );
        REQUIRE(neighbours==expected_neighbours);
    }

    SECTION( "low edge cell's neighbours" ) {
        auto neighbours = a.get_neighbours_state(0, 1);
        auto expected_neighbours = std::vector<bool>( {0, 0, 1, 1, 0, 0, 0, 1} );
        REQUIRE(neighbours==expected_neighbours);
    }

    SECTION( "high edge cell's neighbours" ) {
        auto neighbours = a.get_neighbours_state(2, 1);
        auto expected_neighbours = std::vector<bool>( {1, 0, 0, 0, 1, 1, 0, 0} );
        REQUIRE(neighbours==expected_neighbours);
    }

    SECTION( "left edge cell's neighbours" ) {
        auto neighbours = a.get_neighbours_state(1, 0);
        auto expected_neighbours = std::vector<bool>( {0, 1, 0, 0, 0, 1, 0, 1} );
        REQUIRE(neighbours==expected_neighbours);
    }

    SECTION( "right edge cell's neighbours" ) {
        auto neighbours = a.get_neighbours_state(1, 2);
        auto expected_neighbours = std::vector<bool>( {1, 0, 1, 0, 0, 0, 1, 0} );
        REQUIRE(neighbours==expected_neighbours);
    }

    SECTION( "corner cell's neighbours" ) {
        auto neighbours = a.get_neighbours_state(2, 2);
        auto expected_neighbours = std::vector<bool>( {0, 1, 1, 1, 0, 1, 0, 0} );
        REQUIRE(neighbours==expected_neighbours);
    }
}

TEST_CASE( "grids update properly", "[grid]") {
    SECTION( "block should not change" ) {
        Grid before(4,4);

        before.set_cell_state(0, 0, false);
        before.set_cell_state(0, 1, false);
        before.set_cell_state(0, 2, false);
        before.set_cell_state(0, 3, false);
        before.set_cell_state(1, 0, false);
        before.set_cell_state(1, 1, true);
        before.set_cell_state(1, 2, true);
        before.set_cell_state(1, 3, false);
        before.set_cell_state(2, 0, false);
        before.set_cell_state(2, 1, true);
        before.set_cell_state(2, 2, true);
        before.set_cell_state(2, 3, false);
        before.set_cell_state(3, 0, false);
        before.set_cell_state(3, 1, false);
        before.set_cell_state(3, 2, false);
        before.set_cell_state(3, 3, false);

        auto after = before;

        before.update_grid();

        REQUIRE(before==after);
    }

    SECTION( "blinker should blink" ) {
        Grid before(5,5);
        before.set_cell_state(0, 0, false);
        before.set_cell_state(0, 1, false);
        before.set_cell_state(0, 2, false);
        before.set_cell_state(0, 3, false);
        before.set_cell_state(0, 4, false);
        before.set_cell_state(1, 0, false);
        before.set_cell_state(1, 1, false);
        before.set_cell_state(1, 2, false);
        before.set_cell_state(1, 3, false);
        before.set_cell_state(1, 4, false);
        before.set_cell_state(2, 0, false);
        before.set_cell_state(2, 1, true);
        before.set_cell_state(2, 2, true);
        before.set_cell_state(2, 3, true);
        before.set_cell_state(2, 4, false);
        before.set_cell_state(3, 0, false);
        before.set_cell_state(3, 1, false);
        before.set_cell_state(3, 2, false);
        before.set_cell_state(3, 3, false);
        before.set_cell_state(3, 4, false);
        before.set_cell_state(4, 0, false);
        before.set_cell_state(4, 1, false);
        before.set_cell_state(4, 2, false);
        before.set_cell_state(4, 3, false);
        before.set_cell_state(4, 4, false);

        auto original = before;

        Grid after(5,5);
        after.set_cell_state(0, 0, false);
        after.set_cell_state(0, 1, false);
        after.set_cell_state(0, 2, false);
        after.set_cell_state(0, 3, false);
        after.set_cell_state(0, 4, false);
        after.set_cell_state(1, 0, false);
        after.set_cell_state(1, 1, false);
        after.set_cell_state(1, 2, true);
        after.set_cell_state(1, 3, false);
        after.set_cell_state(1, 4, false);
        after.set_cell_state(2, 0, false);
        after.set_cell_state(2, 1, false);
        after.set_cell_state(2, 2, true);
        after.set_cell_state(2, 3, false);
        after.set_cell_state(2, 4, false);
        after.set_cell_state(3, 0, false);
        after.set_cell_state(3, 1, false);
        after.set_cell_state(3, 2, true);
        after.set_cell_state(3, 3, false);
        after.set_cell_state(3, 4, false);
        after.set_cell_state(4, 0, false);
        after.set_cell_state(4, 1, false);
        after.set_cell_state(4, 2, false);
        after.set_cell_state(4, 3, false);
        after.set_cell_state(4, 4, false);

        before.update_grid();

        REQUIRE(before == after);

        before.update_grid();
        REQUIRE(before == original);
    }
}

TEST_CASE( "data can be loaded from a file", "[util]" ) {
    auto bool_grid = load_from_file("test_grid.txt");
    REQUIRE(bool_grid[0][0] == false);
    REQUIRE(bool_grid[4][4] == false);
    REQUIRE(bool_grid[2][2] == true);
}

TEST_CASE( "grid can be initialised from test file", "[grid]" ) {
}
