use <case_elements.scad>;
include <case_dimensions.scad>;

// file ob_1515.stl was found from:
// http://www.thingiverse.com/thing:30521/#files

module ob_1515(length)
{
    intersection()
    {
        cube([20,20,length]);
        import("ob_1515.stl");
    }
}

module ob_chassis(offset_x, offset_y, offset_z)
{
    // Front, Horizontal
    translate([0,0,ob_width])
        rotate([0, 90, 0])
            ob_1515(300);

    translate([ob_width, 0, 90 + ob_width])
        rotate([0, 90, 0])
            ob_1515(270);

    // Back, Horizontal
    translate([0, lr_height - ob_width, ob_width])
        rotate([0, 90, 0])
            ob_1515(300);

    translate([ob_width, lr_height - ob_width, 90 + ob_width])
        rotate([0, 90, 0])
            ob_1515(270);

    // Left, Vertical
    translate([0,0, ob_width])
        ob_1515(90);
        
    translate([0, 30 + ob_width, ob_width])
        ob_1515(90);

    // Right, Vertical
    translate([300 - ob_width,0, ob_width])
        ob_1515(90);
        
    translate([300 - ob_width, 30 + ob_width, ob_width])
        ob_1515(90);

         
    // Left, Horizontal
    translate([0, ob_width, ob_width])
        rotate([-90, 0, 0])
            ob_1515(30);

           
    translate([0, ob_width, 90 + ob_width])
        rotate([-90, 0, 0])
            ob_1515(30);

    // Right, Horizontal
    translate([300 - ob_width, ob_width, ob_width])
        rotate([-90, 0, 0])
            ob_1515(30);
            
    translate([300 - ob_width, ob_width, 90 + ob_width])
        rotate([-90, 0, 0])
            ob_1515(30);

}

module side_plates()
{
    // Back plate
    translate([0, 60 + 2 * black_thickness, 0])
        rotate([90,0,0]) 
            fb_plate(0,0);

    // Front plate
    translate([0, black_thickness, 0])
        rotate([90,0,0]) 
            fb_plate(0,0);

    // Top plate
    translate([0, black_thickness, fb_height - black_thickness])
        tb_plate(0,0);

    // Bottom plate
    translate([0, black_thickness, 0])
        tb_plate(0,0);

    // Left plate
    translate([black_thickness, black_thickness, black_thickness])
        rotate([0, -90, 0])
            lr_plate(0, 0);

    // Right plate
    translate([fb_width, black_thickness, black_thickness])
        rotate([0, -90, 0])
            lr_plate(0, 0);

    // Mounting plate
    translate([10, 60 - 7.5 + black_thickness, 10])
        rotate([90,0,0]) 
            int_plate(0,0);
}

ob_chassis(black_thickness, black_thickness, black_thickness);

side_plates();
