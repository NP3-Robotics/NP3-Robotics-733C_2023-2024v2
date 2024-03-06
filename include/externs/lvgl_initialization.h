#ifndef _MAIN_H_ // Header guard to make sure no business happens
#define _MAIN_H_
#include "main.h"
#endif

#ifndef _LVGL_INIT_H_ // Header guard to make sure no funny business happens
#define _LVGL_INIT_H_
// Decleartions for the far side six ball button
extern lv_obj_t *far_six_btn;
extern lv_obj_t *far_six_btn_label;

// Decleartions for the far side five ball button
extern lv_obj_t *far_five_btn;
extern lv_obj_t *far_five_btn_label;

// Decleartions for the close side five ball button
extern lv_obj_t *close_five_btn;
extern lv_obj_t *close_five_btn_label;

// Decleartions for the close side four ball button
extern lv_obj_t *close_four_btn;
extern lv_obj_t *close_four_btn_label;

// Decleartion for the skills button
extern lv_obj_t *skills_btn;
extern lv_obj_t *skills_btn_label;

// Declerations for the disabled button
extern lv_obj_t *disable_btn;
extern lv_obj_t *disable_btn_label;

// Button styles
extern lv_style_t scr_style;
extern lv_style_t btn_style_rel;
extern lv_style_t btn_style_pr;
extern lv_style_t btn_style_tgl_rel;
extern lv_style_t btn_style_tgl_pr;
extern lv_style_t label_style;

extern bool auton[]; // Array of button states

extern lv_res_t btn_click(lv_obj_t *btn); // When button is pressed
#endif