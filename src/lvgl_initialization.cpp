#include "externs/lvgl_initialization.h"
#include <iostream>

using namespace std;

lv_obj_t *far_btn;
lv_obj_t *close_btn;
lv_obj_t *disable_btn;
lv_obj_t *skills_btn;
lv_obj_t *skill_issue_btn;

lv_obj_t *far_btn_label;
lv_obj_t *close_btn_label;
lv_obj_t *disable_btn_label;
lv_obj_t *skills_btn_label;
lv_obj_t *skill_issue_btn_label;

lv_style_t scr_style;
lv_style_t btn_style_rel;
lv_style_t btn_style_pr;
lv_style_t btn_style_tgl_rel;
lv_style_t btn_style_tgl_pr;
lv_style_t btn_style_rel_red;
lv_style_t btn_style_pr_red;
lv_style_t btn_style_tgl_rel_red;
lv_style_t btn_style_tgl_pr_red;
lv_style_t btn_style_rel_blue;
lv_style_t btn_style_pr_blue;
lv_style_t btn_style_tgl_rel_blue;
lv_style_t btn_style_tgl_pr_blue;
lv_style_t label_style;

// Decleration of autonomous position
//////////////////////////////////////////
bool closeSide = false;
bool farSide = true;
bool skills = false;
bool disable = false;
//////////////////////////////////////////

// Change autonomous position
//////////////////////////////////////////
lv_res_t btn_click(lv_obj_t *btn)
{
    const int free_num = lv_obj_get_free_num(btn); // Determines which button was pressed

    // Update autonomous side
    //////////////////////////////////////////
    if (free_num == 0) // Close side, left side, or matchloading side button
    {
        closeSide = true;
        farSide = false;
        disable = false;
        skills = false;
    }
    else if (free_num == 1) // Far side, right side, or goal side button
    {
        farSide = true;
        closeSide = false;
        disable = false;
        skills = false;
    }
     else if (free_num == 2) // skills auton button
    {
        farSide = false;
        closeSide = false;
        disable = false;
        skills = true;
    }
    else if (free_num == 3) // disable auton button
    {
        farSide = false;
        closeSide = false;
        disable = true;
        skills = false;
    }
   
    //////////////////////////////////////////
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    // Toggles buttons based on values
    //////////////////////////////////////////
    lv_btn_set_state(close_btn, closeSide);
    lv_btn_set_state(far_btn, farSide);
    lv_btn_set_state(disable_btn, disable);
    lv_btn_set_state(skills_btn, skills);
    //////////////////////////////////////////

    return LV_RES_OK;
}
//////////////////////////////////////////