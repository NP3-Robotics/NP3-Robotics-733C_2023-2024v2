#include "main.h"

#ifndef initLvgl

#define initLvgl

extern lv_obj_t *far_btn;
extern lv_obj_t *close_btn;
extern lv_obj_t *disable_btn;
extern lv_obj_t *skills_btn;
extern lv_obj_t *skill_issue_btn;

extern lv_obj_t *far_btn_label;
extern lv_obj_t *close_btn_label;
extern lv_obj_t *disable_btn_label;
extern lv_obj_t *skills_btn_label;
extern lv_obj_t *skill_issue_btn_label;

extern lv_style_t scr_style;
extern lv_style_t btn_style_rel;
extern lv_style_t btn_style_pr;
extern lv_style_t btn_style_tgl_rel;
extern lv_style_t btn_style_tgl_pr;
extern lv_style_t btn_style_rel_red;
extern lv_style_t btn_style_pr_red;
extern lv_style_t btn_style_tgl_rel_red;
extern lv_style_t btn_style_tgl_pr_red;
extern lv_style_t btn_style_rel_blue;
extern lv_style_t btn_style_pr_blue;
extern lv_style_t btn_style_tgl_rel_blue;
extern lv_style_t btn_style_tgl_pr_blue;
extern lv_style_t label_style;

extern bool farSide;
extern bool closeSide;
extern bool skills;
extern bool disable;

extern lv_res_t btn_click(lv_obj_t *btn);

#endif