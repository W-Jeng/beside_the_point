#pragma once
#include<string>
#include<iostream>
#include<algorithm>

struct Point {
    double x;
    double y;

    Point(double a, double b): x(a), y(b) {}
    
    std::string repr() {
        return "Point(" + std::to_string(x) + "," + std::to_string(y) + ")";
    }
};

bool is_equidistant(const Point& red, const Point& blue) {
    // skip it, not worth the hassle
    if (blue.x == red.x or blue.y == red.y) {
        return true;
    }

    Point mid_point(0.5*(red.x+blue.x), 0.5*(red.y+blue.y));
    double red_blue_gradient = (blue.y - red.y)/(blue.x - red.x);
    double rotated_gradient = -1.0/red_blue_gradient;
    double rotated_constant = mid_point.y - rotated_gradient * mid_point.x;

    // std::cout << "mid point: " << mid_point.repr() << ", rotate_gradient: " << rotated_gradient <<
    //     ", rotated_constant: " << rotated_constant << std::endl;
    // find out which is the closest side
    /*
    4 scenarios
    we need 2 lines y=x and y=1-x to determine the line of closest to the square
    */
    double distance_to_top = 1-blue.y;
    double distance_to_bottom = blue.y;
    double distance_to_left = blue.x;
    double distance_to_right = 1-blue.x;
    double min_distance = std::min({distance_to_top, distance_to_bottom,
        distance_to_left, distance_to_right});

    if (min_distance == distance_to_top) {
        // blue closest to top line y = 1
        // 1 = mx + c;
        // std::cout << "is top line" << std::endl;
        double x_collission_point = (1 - rotated_constant)/rotated_gradient;
        if (0 <= x_collission_point && x_collission_point <= 1) {
            return true;
        }
    } else if (min_distance == distance_to_bottom) {
        // blue closest to bottom line y = 0
        // std::cout << "is bottom line" << std::endl;
        double x_collission_point = (-rotated_constant)/rotated_gradient;
        if (0 <= x_collission_point && x_collission_point <= 1) {
            return true;
        }
    } else if (min_distance == distance_to_left) {
        // blue closest to left line x = 0
        // y = m * 0 +_c
        // std::cout << "is left line" << std::endl;
        double y_collission_point = rotated_constant;
        if (0 <= y_collission_point && y_collission_point <= 1) {
            return true;
        } 
    } else {
        // blue closest to right line x = 1
        // y = m * 1 + c
        // std::cout << "is right line" << std::endl;
        double y_collission_point = rotated_gradient + rotated_constant;
        if (0 <= y_collission_point && y_collission_point <= 1) {
            return true;
        }
    }

    return false;
}