black_thickness = 1.5875;
smoke_thickness = 3.175;

ob_width = 15;
slot_depth = 5;

/****** dimensions ******/
// front/back
fb_width = 300 + 2 * black_thickness;
fb_height = 90 + ob_width + 2 * black_thickness;

// left/right
lr_width = 90 + ob_width;
lr_height = 30 + 2 * ob_width;

// top/bottom
tb_width = fb_width;
tb_height = lr_height;

// mounting plate
int_width = 270 + 2 * slot_depth;
int_height = 90 - ob_width + 2 * slot_depth;