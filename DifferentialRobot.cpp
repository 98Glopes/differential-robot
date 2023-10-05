#include <iostream>
#include <cmath>

class DifferentialRobot {
private:
    double x;               // Initial x position [m]
    double y;               // Initial y position [m]
    double orientation;     // Initial orientation [rad]
    double sample_time;     // Time between each simulation step [s]
    double wheel_diameter; // Wheel diameter [m]
    double axis_distance;  // Distance between the wheels [m]
    double w_right;        // Right wheel speed [rad/s]
    double w_left;         // Left wheel speed [rad/s]

public:
    DifferentialRobot(double init_x, double init_y, double orientation, double sample_time, double R, double L)
        : x(init_x), y(init_y), orientation(orientation), sample_time(sample_time), wheel_diameter(R), axis_distance(L), w_right(0), w_left(0) {}

    void state(bool transpose = false) {
        std::cout << "x: " << x << " y: " << y << " orientation: " << orientation << " linear speed: " << linear_speed() << std::endl;
    }

    void step(double left_wheel_speed, double right_wheel_speed) {
        w_left = left_wheel_speed;
        w_right = right_wheel_speed;

        // Update orientation
        orientation += (wheel_diameter / axis_distance) * (w_right - w_left) * sample_time;

        // Update x position
        x += (wheel_diameter / 2) * cos(orientation) * (w_right + w_left) * sample_time;

        // Update y position
        y += (wheel_diameter / 2) * sin(orientation) * (w_right + w_left) * sample_time;
    }

    std::pair<double, double> inputs() {
        return std::make_pair(w_left, w_right);
    }

    double linear_speed() {
        return (wheel_diameter / 2) * (w_right + w_left);
    }
};

int main() {
    DifferentialRobot robot(0.0, 0.0, 0.0, 0.1, 0.1, 0.2); // Example initialization
    robot.state(); // Example output

    return 0;
}
