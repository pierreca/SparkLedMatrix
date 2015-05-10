include <case_dimensions.scad>

module black_plate(width, height)
{
    color("black")
        cube([width, height, black_thickness]);   
}

module smoke_plate(width, height)
{
    color("gray")
        cube([width, height, black_thickness]);   
}

module hole(offset_x, offset_y)
{
    translate([offset_x, offset_y, 0])
        cylinder(h=10, r=2, center=true);
}

module fb_plate(offset_x, offset_y) 
{
    a = 20 + black_thickness;
    b = 7.5 + black_thickness;
    
    translate([offset_x, offset_y, 0])
        difference()
        {
            black_plate(fb_width, fb_height);
            hole(a, b);
            hole(b, a);
            hole(b, fb_height - a);
            hole(a, fb_height - b);
            hole(fb_width - a, b);
            hole(fb_width - b, a);
            hole(fb_width - a, fb_height - b);
            hole(fb_width - b, fb_height - a);
        }
}

module lr_plate(offset_x, offset_y) 
{
    a = 20;
    b = 7.5;
    
    translate([offset_x, offset_y, 0])
        difference()
        {
            black_plate(lr_width, lr_height);
            hole(a, b);
            hole(b, a);
            hole(b, lr_height - a);
            hole(a, lr_height - b);
            hole(lr_width - a, b);
            hole(lr_width - b, a);
            hole(lr_width - a, lr_height - b);
            hole(lr_width - b, lr_height - a);
        }
}

module tb_plate(offset_x, offset_y) 
{
    a = 20 + black_thickness;
    b = 7.5 + black_thickness;
    c = 20;
    d = 7.5;
    
    translate([offset_x, offset_y, 0])
        difference()
        {
            black_plate(tb_width, tb_height);
            hole(a, d);
            hole(b, c);
            hole(b, tb_height - c);
            hole(a, tb_height - d);
            hole(tb_width - a, d);
            hole(tb_width - b, c);
            hole(tb_width - a, tb_height - d);
            hole(tb_width - b, tb_height - c);
        }
}

module int_plate(offset_x, offset_y)
{
    translate([offset_x, offset_y, 0])
        black_plate(int_width, int_height);
}

module front_plate()
{
    fb_plate(0,0);
}