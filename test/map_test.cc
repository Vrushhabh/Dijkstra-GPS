//
// Created by Vrushhabh Patel on 4/26/21.
//
#include <gps/map.h>
#include <catch2/catch.hpp>

using pathfinder::Space;

TEST_CASE("Map and Space test") {
    pathfinder::Map map;
    Space space_0 = Space(0);
    Space space_1 = Space(1);
    Space space_2 = Space(2);
    Space space_3 = Space(3);

    map.AddSpace(space_0);
    map.AddSpace(space_1);
    map.AddSpace(space_2);
    map.AddSpace(space_3);
    //First parameter is the weight and the second and third are the spaces where the connections are
    //being made
    //Straight line to destination
    map.AddConnection(3, 0, 1);
    map.AddConnection(3, 1, 2);
    map.AddConnection(3, 2, 3);

    SECTION("Check for nonexistent spaces") {
        REQUIRE_THROWS(map.FindShortestPath(5, 5),
        std::invalid_argument("Space does not exist in map currently"));
    }

    SECTION("When starting space is the destination") {
        REQUIRE(map.FindShortestPath(0, 0) == 0);
    }
    SECTION("When starting space is adjacent to destination") {
        REQUIRE(map.FindShortestPath(0, 1) == 3);
    }
    SECTION("When starting space is 2 connections over from to destination") {
        REQUIRE(map.FindShortestPath(0, 2) == 6);
    }
    SECTION("When starting space is 3 connections over from to destination") {
        REQUIRE(map.FindShortestPath(0, 3) == 9);
    }
    SECTION("When starting space is not zero") {
        REQUIRE(map.FindShortestPath(2, 3) == 3);
    }
    SECTION("Cyclic connection that is shorter than a possible other connection") {
        //Cyclic connection between spaces on map
        Space space_4 = Space(4);
        map.AddSpace(space_4);
        map.AddConnection(3,0,4);
        map.AddConnection(3,4,3);
        REQUIRE(map.FindShortestPath(0, 3) == 6);
    }



}