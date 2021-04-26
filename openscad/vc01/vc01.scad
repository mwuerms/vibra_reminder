/**
 * Martin Egli
 * 2021-03-19
 * case for vibra reminder, pcb v01
 */
res = 50;
project_text = "vc01,v3";

module pcb(th = 1.6, pcb_col = "Green") {
    color(pcb_col) {
        difference() {
            hull() {
                translate([5.5, 5.5, 0])
                cylinder(r = 5.5, h = th, $fn = res);
                translate([33-5.5, 5.5, 0])
                cylinder(r = 5.5, h = th, $fn = res);
                translate([5.5, 44-5.5, 0])
                cylinder(r = 5.5, h = th, $fn = res);
                translate([33-5.5, 44-5.5, 0])
                cylinder(r = 5.5, h = th, $fn = res);
            }
            hull() {
                translate([3, 7, -0.5])
                cylinder(d = 2, h = th+1, $fn = res);
                translate([3, 44-7, -0.5])
                cylinder(d = 2, h = th+1, $fn = res);
            }
            hull() {
                translate([30, 7, -0.5])
                cylinder(d = 2, h = th+1, $fn = res);
                translate([30, 44-7, -0.5])
                cylinder(d = 2, h = th+1, $fn = res);
            }
        }
    }
    color("Black") {
        // micro USB 10104110
        translate([12.5, 0, th])
        cube([8, 6.5, 3]);
        // on switch PCM12SMTR
        translate([5.5, 15.5, th])
        cube([3, 7, 1.4]);
        // user switch PCM12SMTR
        translate([24.5, 15.5, th])
        cube([3, 7, 1.4]);
        // ATTiny85, SOIC-8
        translate([16.5, 13, th])
        cube([6, 6, 2.2]);
    }
    color("Gold") {
        // akku 40 x 18 x 5 mm
        translate([7.5, 2, th+3])
        cube([18, 40, 5]);
    }
}

module case(th = 9, case_col = "Silver", wall_th = 1) {
    color(case_col) {
        difference() {
            /*hull() {
                translate([2, 2, 0]) {
                    translate([0, 0, 0])
                    cylinder(r = 2, h = th-2, $fn = res);
                    translate([0, 0, th-2])
                    sphere(r = 2, $fn = res);
                }
                translate([20, 2, 0]) {
                    translate([0, 0, 0])
                    cylinder(r = 2, h = th-2, $fn = res);
                    translate([0, 0, th-2])
                    sphere(r = 2, $fn = res);
                }
                translate([2, 44-2, 0]) {
                    translate([0, 0, 0])
                    cylinder(r = 2, h = th-2, $fn = res);
                    translate([0, 0, th-2])
                    sphere(r = 2, $fn = res);
                }
                translate([20, 44-2, 0]) {
                    translate([0, 0, 0])
                    cylinder(r = 2, h = th-2, $fn = res);
                    translate([0, 0, th-2])
                    sphere(r = 2, $fn = res);
                }
            }*/
            union() {
                hull() {
                    translate([2, 0, 0])
                    cube([18, 44, th-2]);
                    translate([0, 2, 0])
                    cube([22, 40, th-2]);
                    translate([2, 2, th-2])
                    cube([18, 40, 2]);
                }
                translate([-5.5, 0, 0])
                hull() {
                    translate([5.5, 5.5, 0])
                    cylinder(r = 5.5, h = 1, $fn = res);
                    translate([33-5.5, 5.5, 0])
                    cylinder(r = 5.5, h = 1, $fn = res);
                    translate([5.5, 44-5.5, 0])
                    cylinder(r = 5.5, h = 1, $fn = res);
                    translate([33-5.5, 44-5.5, 0])
                    cylinder(r = 5.5, h = 1, $fn = res);
                }
            }
            // inner cut out
            /*hull() {
                translate([2, 2, 0]) {
                    translate([0, 0, 1])
                    cylinder(r = 2-1, h = th-3, $fn = res);
                    translate([0, 0, th-2])
                    sphere(r = 2-1, $fn = res);
                }
                translate([20, 2, 0]) {
                    translate([0, 0, 1])
                    cylinder(r = 2-1, h = th-3, $fn = res);
                    translate([0, 0, th-2])
                    sphere(r = 2-1, $fn = res);
                }
                translate([2, 44-2, 0]) {
                    translate([0, 0, 1])
                    cylinder(r = 2-1, h = th-3, $fn = res);
                    translate([0, 0, th-2])
                    sphere(r = 2-1, $fn = res);
                }
                translate([20, 44-2, 0]) {
                    translate([0, 0, 1])
                    cylinder(r = 2-1, h = th-3, $fn = res);
                    translate([0, 0, th-2])
                    sphere(r = 2-1, $fn = res);
                }
            }*/
            hull() {
                    translate([3, 1, 0])
                    cube([16, 42, th-3]);
                    translate([1, 2, 0])
                    cube([20, 38, th-3]);
                    translate([3, 3, th-3])
                    cube([16, 38, 2]);
                }
            hull() {
                translate([2+2, 2+2, 0]) {
                    translate([0, 0, -1])
                    cylinder(r = 2+1, h = 3, $fn = res);
                }
                translate([20-2, 2+2, 0]) {
                    translate([0, 0, -1])
                    cylinder(r = 2+1, h = 3, $fn = res);
                }
                translate([2+2, 44-4, 0]) {
                    translate([0, 0, -1])
                    cylinder(r = 2+1, h = 3, $fn = res);
                }
                translate([20-2, 44-4, 0]) {
                    translate([0, 0, -1])
                    cylinder(r = 2+1, h = 3, $fn = res);
                }
            }
            // holder wings cutouts
            hull() {
                translate([3-5.5, 7, -0.5])
                cylinder(d = 2, h = 2, $fn = res);
                translate([3-5.5, 44-7, -0.5])
                cylinder(d = 2, h = 2, $fn = res);
            }
            translate([3-5.5, 6, -0.5])
            cube([2.5, 32, 2]);
            hull() {
                translate([30-5.5, 7, -0.5])
                cylinder(d = 2, h = 2, $fn = res);
                translate([30-5.5, 44-7, -0.5])
                cylinder(d = 2, h = 2, $fn = res);
            }
            translate([30-5.5-2.5, 6, -0.5])
            cube([2.5, 32, 2]);

            // micro USB 10104110
            translate([6.8, -1, -1]) 
            cube([8.4, 3, 4.2]);
            // LED ch stat
            translate([20, 7, 1])
            rotate([0, 90, 0])
            cylinder(d = 1, h = 3, $fn = res);
            // LED user
            translate([20, 10, 1])
            rotate([0, 90, 0])
            cylinder(d = 1, h = 3, $fn = res);
            // on switch PCM12SMTR
            translate([-0.5, 15.5, -1])
            cube([3, 7, 2.5]);
            // user switch PCM12SMTR
            translate([20, 15.5, -1])
            cube([3, 7, 2.5]);

            // cut to see inside
            /*translate([-1, -1, -1])
            cube([30, 22, 20]);*/
            
            translate([18, 4, 8.3])
            rotate([180, 0, 180])
            linear_extrude(1)
            text(project_text, 3, $fn = res);
        }
    }
}

translate([5.5, 0, 0]) case();
//translate([0, 0, -1.6]) pcb();
