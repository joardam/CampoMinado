#include <vector>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "GameFunctions.h"


constexpr auto HOUSE_EMPTY = 0;
constexpr auto HOUSE_1_NEAR_BOMB = 1;
constexpr auto HOUSE_2_NEAR_BOMB = 2;
constexpr auto HOUSE_3_NEAR_BOMB = 3;
constexpr auto HOUSE_4_NEAR_BOMB = 4;
constexpr auto HOUSE_5_NEAR_BOMB = 5;
constexpr auto HOUSE_6_NEAR_BOMB = 6;
constexpr auto HOUSE_7_NEAR_BOMB = 7;
constexpr auto HOUSE_8_NEAR_BOMB = 8;
constexpr auto HOUSE_BOMB = 9;
constexpr auto HOUSE_COVERED = 10;
constexpr auto FLAG = 11;
constexpr auto HOUSE_COVERED_BOMB = 12;
constexpr auto HOUSE_LAMP = 13;
