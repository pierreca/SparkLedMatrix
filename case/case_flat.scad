use <case_elements.scad>;
include <case_dimensions.scad>;

$fs = 0.1;

fb_plate(0,0);

tb_plate(0, fb_height + 5);
tb_plate(0, fb_height + 5 + tb_height + 5);

int_plate(0, fb_height + 5 + 2 * (tb_height + 5));

lr_plate(0, fb_height + 5 + 2 * (tb_height + 5) + int_height + 5);
lr_plate(lr_width + 5, fb_height + 5 + 2 * (tb_height + 5) + int_height + 5);

