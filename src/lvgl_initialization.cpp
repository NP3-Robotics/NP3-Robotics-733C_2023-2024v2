#include "main.h"
#include <iostream>

// Button decleration for far side six ball autonomous
lv_obj_t *far_six_btn;
lv_obj_t *far_six_btn_label;

// Button decleration for far side five ball autonomous
lv_obj_t *far_five_btn;
lv_obj_t *far_five_btn_label;

// Button decleration for close side win point autonomous
lv_obj_t *close_awp_btn;
lv_obj_t *close_awp_btn_label;

// Button decleration for close side mid rush autonomous
lv_obj_t *close_elim_btn;
lv_obj_t *close_elim_btn_label;

// Button decleration for close side mid rush autonomous
lv_obj_t *skills_btn;
lv_obj_t *skills_btn_label;

lv_obj_t *disable_btn;
lv_obj_t *disable_btn_label;

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


bool auton[] = {false, false, false, false, false, true}; // Autonomous program {Close AWP, Close Elims, Far Six Ball, Far Five Ball, Skills Auton, Disabled Auton}

lv_res_t btn_click(lv_obj_t *btn) // When button is pressed
{
    const int free_num = lv_obj_get_free_num(btn); // Determines which button was pressed

    for (int i = 0; i < 6; i++) // Sets all values in auton list to false
        auton[i] = false;
    
    auton[free_num] = true; // Sets selected button to true

    // Toggles buttons based on values
    //////////////////////////////////////////
    lv_btn_set_state(close_awp_btn, auton[0]);
    lv_btn_set_state(close_elim_btn, auton[1]);
    lv_btn_set_state(far_six_btn, auton[2]);
    lv_btn_set_state(far_five_btn, auton[3]);
    lv_btn_set_state(skills_btn, auton[4]);
    lv_btn_set_state(disable_btn, auton[5]);
    //////////////////////////////////////////

    return LV_RES_OK;
}