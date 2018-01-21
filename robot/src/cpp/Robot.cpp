#include "WPILib.h"
#include "AHRS.h"
#include "ctre/phoenix/MotorControl/CAN/TalonSRX.h"

#include "drivetrain.h"

using namespace ctre::phoenix::motorcontrol;

// I'd hope your robot code is more separated than this
// (i.e. has some form of IO management class), but this will
// do for the demonstration of how this whole project goes together.

class MyRobot : public frc::TimedRobot {
public:
  subsystems::coupled_drivetrain drivetrain;
  frc::Joystick *joy;
  AHRS *navx;
  can::TalonSRX *talon_left, *talon_right; // assuming 1 motor per side

  MyRobot() : drivetrain(6, 1.0, 10) {}

  void RobotInit() {
    joy = new frc::Joystick(0);
    navx = new AHRS(frc::I2C::Port::kOnboard);
    talon_left = new can::TalonSRX(0);
    talon_right = new can::TalonSRX(1);
  }

  void TeleopPeriodic() override {
    double heading = joy->GetDirectionDegrees();
    double speed = joy->GetMagnitude();
    double gyro = navx->GetAngle();

    auto result = drivetrain.calculate_angular(heading, speed, gyro);
    talon_left->Set(ControlMode::PercentOutput, result.left_volts / talon_left->GetBusVoltage());
    talon_right->Set(ControlMode::PercentOutput, result.right_volts / talon_right->GetBusVoltage());
  }
};

START_ROBOT_CLASS(MyRobot)