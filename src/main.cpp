#include "main.h"
#include "lemlib/api.hpp"

#include "externs/drivetrain_initialization.h"
#include "externs/lvgl_initialization.h"
#include "externs/robot_functions_initialization.h"

void initialize()
{
  // Motor brake mode initialization
  //////////////////////////////////////////
  leftMtrs.set_brake_modes(pros::E_MOTOR_BRAKE_COAST); // Left motors will not actively resist turning
  rightMtrs.set_brake_modes(pros::E_MOTOR_BRAKE_COAST); // Right motors will not actively resist turning

  cata.set_brake_mode(pros::E_MOTOR_BRAKE_COAST); // Catapult motor will not actively resist turning
  intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST); // Intake motor will not actively resist turning
  //////////////////////////////////////////





  // Lvgl initialization
  //////////////////////////////////////////
  lv_style_copy(&scr_style, &lv_style_plain);
  scr_style.body.radius = 0;
  scr_style.body.main_color = LV_COLOR_BLACK;
  scr_style.body.grad_color = LV_COLOR_BLACK;
  scr_style.body.border.part = LV_BORDER_NONE;
  scr_style.text.color = LV_COLOR_WHITE;

  lv_obj_set_style(lv_scr_act(), &scr_style);
  //////////////////////////////////////////




  /*
  // Temperature and battery checks
  //////////////////////////////////////////
  for (int i = 0; i < sizeof(leftMtrs.get_temperatures()); i++) // For the left motors
  {
    if (leftMtrs.get_temperatures()[i] >= 55) // Checks if the left motor is running at 50% capacity
    {
      std::cout << "Left motor #" << i + 1 << " over heating at " << leftMtrs.get_temperatures()[i] << std::endl;
      controller.rumble("- - - - ");
    }
  }

  for (int i = 0; i < sizeof(rightMtrs.get_temperatures()); i++) 
  {
    if (rightMtrs.get_temperatures()[i] >= 55) // Checks if the right motor is running at 50% capacity
    {
      std::cout << "Right motor #" << i+1 << " over heating at " << rightMtrs.get_temperatures()[i] << std::endl;
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
    controller.rumble("-");
  }
  //////////////////////////////////////////
  */




  base.calibrate(); // Calibrate base sensors
}

void disabled() {} // Has no use

void competition_initialize()
{
  std::cout<< "buttons done" << std::endl;

  // Initialize lvgl buttons
  //////////////////////////////////////////
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

  close_btn = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_free_num(close_btn, 0);
  lv_btn_set_action(close_btn, LV_BTN_ACTION_CLICK, btn_click);
  lv_obj_set_size(close_btn, 225, 67);
  lv_obj_align(close_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);
  lv_btn_set_style(close_btn, LV_BTN_STYLE_REL, &btn_style_rel);
  lv_btn_set_style(close_btn, LV_BTN_STYLE_PR, &btn_style_pr);
  lv_btn_set_style(close_btn, LV_BTN_STYLE_TGL_REL, &btn_style_tgl_rel);
  lv_btn_set_style(close_btn, LV_BTN_STYLE_TGL_PR, &btn_style_tgl_pr);
  close_btn_label = lv_label_create(close_btn, NULL);
  lv_label_set_style(close_btn_label, &label_style);
  lv_label_set_text(close_btn_label, "Close/Left Side");

  far_btn = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_free_num(far_btn, 1);
  lv_btn_set_action(far_btn, LV_BTN_ACTION_CLICK, btn_click);
  lv_obj_set_size(far_btn, 225, 67);
  lv_obj_align(far_btn, NULL, LV_ALIGN_IN_TOP_RIGHT, -10, 10);
  lv_btn_set_style(far_btn, LV_BTN_STYLE_REL, &btn_style_rel);
  lv_btn_set_style(far_btn, LV_BTN_STYLE_PR, &btn_style_pr);
  lv_btn_set_style(far_btn, LV_BTN_STYLE_TGL_REL, &btn_style_tgl_rel);
  lv_btn_set_style(far_btn, LV_BTN_STYLE_TGL_PR, &btn_style_tgl_pr);
  far_btn_label = lv_label_create(far_btn, NULL);
  lv_label_set_style(far_btn_label, &label_style);
  lv_label_set_text(far_btn_label, "Far/Right Side");

  skills_btn = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_free_num(skills_btn, 2);
  lv_btn_set_action(skills_btn, LV_BTN_ACTION_CLICK, btn_click);
  lv_obj_set_size(skills_btn, 225, 67);
  lv_obj_align(skills_btn, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 10, -10);
  lv_btn_set_style(skills_btn, LV_BTN_STYLE_REL, &btn_style_rel);
  lv_btn_set_style(skills_btn, LV_BTN_STYLE_PR, &btn_style_pr);
  lv_btn_set_style(skills_btn, LV_BTN_STYLE_TGL_REL, &btn_style_tgl_rel);
  lv_btn_set_style(skills_btn, LV_BTN_STYLE_TGL_PR, &btn_style_tgl_pr);
  skills_btn_label = lv_label_create(skills_btn, NULL);
  lv_label_set_style(skills_btn_label, &label_style);
  lv_label_set_text(skills_btn_label, "Skills Auton");

  disable_btn = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_free_num(disable_btn, 3);
  lv_btn_set_action(disable_btn, LV_BTN_ACTION_CLICK, btn_click);
  lv_obj_set_size(disable_btn, 225, 67);
  lv_obj_align(disable_btn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -10);
  lv_btn_set_style(disable_btn, LV_BTN_STYLE_REL, &btn_style_rel);
  lv_btn_set_style(disable_btn, LV_BTN_STYLE_PR, &btn_style_pr);
  lv_btn_set_style(disable_btn, LV_BTN_STYLE_TGL_REL, &btn_style_tgl_rel);
  lv_btn_set_style(disable_btn, LV_BTN_STYLE_TGL_PR, &btn_style_tgl_pr);
  disable_btn_label = lv_label_create(disable_btn, NULL);
  lv_label_set_style(disable_btn_label, &label_style);
  lv_label_set_text(disable_btn_label, "Disable Auton");

  skill_issue_btn = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_free_num(skill_issue_btn, 0);
  lv_btn_set_action(skill_issue_btn, LV_BTN_ACTION_CLICK, btn_click);
  lv_obj_set_size(skill_issue_btn, 225, 67);
  lv_obj_align(skill_issue_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);
  lv_btn_set_style(skill_issue_btn, LV_BTN_STYLE_REL, &btn_style_rel);
  lv_btn_set_style(skill_issue_btn, LV_BTN_STYLE_PR, &btn_style_pr);
  lv_btn_set_style(skill_issue_btn, LV_BTN_STYLE_TGL_REL, &btn_style_tgl_rel);
  lv_btn_set_style(skill_issue_btn, LV_BTN_STYLE_TGL_PR, &btn_style_tgl_pr);
  skill_issue_btn_label = lv_label_create(skill_issue_btn, NULL);
  lv_label_set_style(skill_issue_btn_label, &label_style);
  lv_label_set_text(skill_issue_btn_label, "Close/Left Side");
  //////////////////////////////////////////





  // Sets the buttons to their default state
  //////////////////////////////////////////
  lv_btn_set_state(close_btn, closeSide);
  lv_btn_set_state(far_btn, farSide);
  lv_btn_set_state(disable_btn, disable);
  lv_btn_set_state(skills_btn, skills);
  //////////////////////////////////////////
}