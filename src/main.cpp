// External libraries
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
///////////////////////////////////////////////////////////////////////////////////////////////////////////





// My global variables
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "externs/drivetrain_initialization.h"
#include "externs/lvgl_initialization.h"
#include "externs/robot_functions_initialization.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////





void initialize()
{
  // Motor brake mode initialization
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  prosLeftMtrs.set_brake_modes(pros::E_MOTOR_BRAKE_COAST); // Left motors will not actively resist turning
  prosRightMtrs.set_brake_modes(pros::E_MOTOR_BRAKE_COAST); // Right motors will not actively resist turning

  cata.set_brake_mode(pros::E_MOTOR_BRAKE_COAST); // Catapult motor will not actively resist turning
  cata.tare_position();
  intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST); // Intake motor will not actively resist turning
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////





  // Lvgl initialization
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  lv_style_copy(&scr_style, &lv_style_plain);
  scr_style.body.radius = 0;
  scr_style.body.main_color = LV_COLOR_BLACK;
  scr_style.body.grad_color = LV_COLOR_BLACK;
  scr_style.body.border.part = LV_BORDER_NONE;
  scr_style.text.color = LV_COLOR_WHITE;

  lv_obj_set_style(lv_scr_act(), &scr_style);
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////



  /*
  // Temperature and battery checks
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < sizeof(prosLeftMtrs.get_temperatures()); i++) // For the left motors
  {
    if (prosLeftMtrs.get_temperatures()[i] >= 55) // Checks if the left motor is running at 50% capacity
    {
      std::cout << "Left motor #" << i + 1 << " over heating at " << prosLeftMtrs.get_temperatures()[i] << std::endl;
      controller.rumble("- - - - ");
    }
  }

  for (int i = 0; i < sizeof(prosRightMtrs.get_temperatures()); i++) 
  {
    if (prosRightMtrs.get_temperatures()[i] >= 55) // Checks if the right motor is running at 50% capacity
    {
      std::cout << "Right motor #" << i+1 << " over heating at " << prosRightMtrs.get_temperatures()[i] << std::endl;
      controller.rumble("- - - - ");
    }
  }

  if (cata.get_temperature() >= 55) // Checks if the Catapult motor is running at 50% capacity
  {
    std::cout << "Catapult motor over heating at " << cata.get_temperature() << std::endl;
    controller.rumble("- . - . ");
  }

  if (intake.get_temperature() >= 55) // Checks if the intake motor is running at 50% capacity
  {
    std::cout << "Intake motor over heating at " << intake.get_temperature() << std::endl;
    controller.rumble(". - . - ");
  }

  if (controller.get_battery_level() <= 15) // Checks if the battery is 15% or below
  {
    std::cout << "Battery low at " << controller.get_battery_level() << std::endl;
    controller.rumble("- - -");
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  */




  base.calibrate(); // Calibrate base sensors
}

void disabled() {} // Has no use

// Initialize lvgl buttons
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void buttonInitialization(lv_obj_t* button, int freenum, int x, int y, int* dimensions, lv_obj_t* button_label, const char* button_name) // Process of creating a button
{
  lv_obj_set_free_num(button, freenum);
  lv_btn_set_action(button, LV_BTN_ACTION_CLICK, btn_click);
  lv_obj_set_size(button, dimensions[0], dimensions[1]);
  lv_obj_align(button, NULL, LV_ALIGN_CENTER, x, y);
  lv_btn_set_style(button, LV_BTN_STYLE_REL, &btn_style_rel);
  lv_btn_set_style(button, LV_BTN_STYLE_PR, &btn_style_pr);
  lv_btn_set_style(button, LV_BTN_STYLE_TGL_REL, &btn_style_tgl_rel);
  lv_btn_set_style(button, LV_BTN_STYLE_TGL_PR, &btn_style_tgl_pr);
  
  lv_label_set_style(button_label, &label_style);
  lv_label_set_text(button_label, button_name);
}

void competition_initialize()
{
  std::cout<< "Buttons done" << std::endl;

  // Definition of button styles/looks
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  lv_style_copy(&btn_style_rel, &lv_style_plain);
  btn_style_rel.body.radius = 0;
  btn_style_rel.body.main_color = LV_COLOR_PURPLE;
  btn_style_rel.body.grad_color = LV_COLOR_PURPLE;
  btn_style_rel.body.border.part = LV_BORDER_NONE;
  btn_style_rel.text.color = LV_COLOR_WHITE;

  lv_style_copy(&btn_style_pr, &lv_style_plain);
  btn_style_pr.body.radius = 0;
  btn_style_pr.body.main_color = LV_COLOR_MAGENTA;
  btn_style_pr.body.grad_color = LV_COLOR_MAGENTA;
  btn_style_pr.body.border.part = LV_BORDER_NONE;
  btn_style_pr.text.color = LV_COLOR_WHITE;

  lv_style_copy(&btn_style_tgl_rel, &lv_style_plain);
  btn_style_tgl_rel.body.radius = 0;
  btn_style_tgl_rel.body.main_color = LV_COLOR_PURPLE;
  btn_style_tgl_rel.body.grad_color = LV_COLOR_PURPLE;
  btn_style_tgl_rel.body.border.color = LV_COLOR_WHITE;
  btn_style_pr.body.border.part = LV_BORDER_NONE;
  btn_style_tgl_rel.text.color = LV_COLOR_WHITE;

  lv_style_copy(&btn_style_tgl_pr, &lv_style_plain);
  btn_style_tgl_pr.body.radius = 0;
  btn_style_tgl_pr.body.main_color = LV_COLOR_MAGENTA;
  btn_style_tgl_pr.body.grad_color = LV_COLOR_MAGENTA;
  btn_style_tgl_pr.body.border.color = LV_COLOR_WHITE;
  btn_style_pr.body.border.part = LV_BORDER_NONE;
  btn_style_tgl_pr.text.color = LV_COLOR_WHITE;

  lv_style_copy(&label_style, &lv_style_plain);
  label_style.text.color = LV_COLOR_WHITE;
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Screen dimensions are 480x240 pixels
  static int buttonDimensions[] = {225, 67};

  // Defintion of specific buttons
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Close side five button defitnion
  close_five_btn = lv_btn_create(lv_scr_act(), NULL);
  close_five_btn_label = lv_label_create(close_five_btn, NULL);

  // Close side fourinations button defintion
  close_four_btn = lv_btn_create(lv_scr_act(), NULL);
  close_four_btn_label = lv_label_create(close_four_btn, NULL);

  // Far side six ball button definition
  far_six_btn = lv_btn_create(lv_scr_act(), NULL);
  far_six_btn_label = lv_label_create(far_six_btn, NULL);

  // Far side five ball button definition
  far_five_btn = lv_btn_create(lv_scr_act(), NULL);
  far_five_btn_label = lv_label_create(far_five_btn, NULL);

  // Skills button definition
  skills_btn = lv_btn_create(lv_scr_act(), NULL);
  skills_btn_label = lv_label_create(skills_btn, NULL);

  // Disabled autonomous defintion
  disable_btn = lv_btn_create(lv_scr_act(), NULL);
  disable_btn_label = lv_label_create(disable_btn, NULL);

  // Creates the buttons on the screen
  buttonInitialization(close_five_btn, 0, -127, 86, buttonDimensions, close_five_btn_label, "Close Five Ball");
  buttonInitialization(close_four_btn, 1, -127, 0, buttonDimensions, close_four_btn_label, "Close Four Ball");
  buttonInitialization(far_six_btn, 2, 127, 86, buttonDimensions, far_six_btn_label, "Far Six Ball");
  buttonInitialization(far_five_btn, 3, 127, 0, buttonDimensions, far_five_btn_label, "Far Five Ball");
  buttonInitialization(skills_btn, 4, -127, -86, buttonDimensions, skills_btn_label, "Skills Auton");
  buttonInitialization(disable_btn, 5, 127, -86, buttonDimensions, disable_btn_label, "Disabled Auton");
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////





  // Sets the buttons to their default state
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  lv_btn_set_state(close_five_btn, auton[0]);
  lv_btn_set_state(close_four_btn, auton[1]);
  lv_btn_set_state(far_six_btn, auton[2]);
  lv_btn_set_state(far_five_btn, auton[3]);
  lv_btn_set_state(skills_btn, auton[4]);
  lv_btn_set_state(disable_btn, auton[5]);
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////