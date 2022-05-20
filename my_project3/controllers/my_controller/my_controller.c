#include <webots/altimeter.h>
#include <webots/led.h>
#include <webots/motor.h>
#include <webots/robot.h>

#include <stdio.h>

int main(int argc, char **argv) {
  wb_robot_init();
  int time_step = (int)wb_robot_get_basic_time_step();

  // Get the altimeter and enable it.
  WbDeviceTag altimeter = wb_robot_get_device("altimeter");
  wb_altimeter_enable(altimeter, time_step);

  // Get the motors, and set them to allow the wheels to roll freely
  WbDeviceTag left_motor = wb_robot_get_device("left wheel motor");
  WbDeviceTag right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);

  bool direction_switch = false;

  while (wb_robot_step(time_step) != -1) {
    double altitude = wb_altimeter_get_value(altimeter);
    if (!direction_switch) {
      wb_motor_set_velocity(left_motor, 2.0);
      wb_motor_set_velocity(right_motor, 2.0);
      if (altitude <= 0.05)
        direction_switch = true;
    } else {
      wb_motor_set_velocity(left_motor, -2.0);
      wb_motor_set_velocity(right_motor, -2.0);
      if (altitude >= 0.25)
        direction_switch = false;
    }
  };

  wb_robot_cleanup();
  return 0;
}
