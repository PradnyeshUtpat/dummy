//Applications of Barnes Hut Algorithm

//Include Libraries & files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Octree.h"
#include "Quadtree.h"
#include "Applications.h"

//1. satellites() :
void sat(char *filename){
    float x, y, z, m, x1, y1;
    //Following Variables are system bounds
    float xlow, xhigh, ylow, yhigh, zlow, zhigh;
    //Following Variables are test points for force
    float xtest, ytest, ztest, mtest, xtest1, ytest1;
    //size variable is number of nodes mentioned in text files
    int size;
    //Memory is allocated
    octree *o = malloc(sizeof(octree));
    //If memory doesn't exist or unreachable
    if (!o)
        return;
    //FRONT END 
    printf("\n--------------------------------------------------------------------");
    printf("\n The following test system is built with real time satellite data:");
    printf("\nNOTE: All values are w.r.t. a constant time in order to get accurate results");
    printf("\n--------------------------------------------------------------------");
    printf("\nThe following satellites were considered for this experiment : ");
    printf("\n1. The International Space Station");
    printf("\n2. Hubble Space Telescope");
    printf("\n3. Fenyung 1c");
    printf("\n4. IBEX - NASA");
    printf("\n5. Chandrayaan 2");
    printf("\n6. Vela 1");
    printf("\n7. Sirius 1");
    printf("\n8. Oscar 17");
    printf("\n--------------------------------------------------------------------");
    printf("\nThe system bounds have been set as follows for test purposes : ");
    printf("\nx & y (-1,00,000 to 1,00,000) z (-10,00,000 to 10,00,000)");
    printf("\n--------------------------------------------------------------------");
    FILE *f;
    f = fopen(filename, "r");
    if(f == NULL) {
        printf("File can't open");
        return;
    }
    
    fscanf(f, "%f", &xlow);
    fscanf(f, "%f", &ylow);
    fscanf(f, "%f", &zlow);
    fscanf(f, "%f", &xhigh);
    fscanf(f, "%f", &yhigh);
    fscanf(f, "%f", &zhigh);
    if((xlow == xhigh) && (ylow == yhigh) && (zlow == zhigh)){
        printf("\nInvalid System bounds!");
        return;
    }
    
    //System bounds must be positively & negatively greater than the system
    o = BarnesHut3D_init(xlow, xhigh, ylow, yhigh, zlow, zhigh);
    
    fscanf(f, "%d", &size);
    for(int i = 0; i < size; i++){
        fscanf(f, "%f", &y);
        fscanf(f, "%f", &x);
        fscanf(f, "%f", &z);
        fscanf(f, "%f", &m);
        /* Valid Latitudes - -90 to 90
           Valid Longitudes - -179 to 179
           Valid Altitudes - Above 100 Km 
           Valid Mass - Greater than 0*/
        if ((y > 90) || (y < -90) || (x > 179) || (x < -179) || (z < 100) || (m < 1)) {
            printf("\nInvalid System!");
            return;
        }
        //Convert Latitude & Longitude to Km
        y1 = convert_latitude(y);
        x1 = convert_longitude(x);
        BarnesHut3D_insert(o, x1, y1, z, m);
    }
    printf("\n1. Total Number of satellites added to system: %d", o->leaves);
    printf("\n--------------------------------------------------------------------");
    printf("\nThe system is built as follows : \n");
    BarnesHut3D_display(o);
    printf("\n--------------------------------------------------------------------");
    BarnesHut3D_tree_calculate(o);
    printf("\n2.Centre of mass x coordinate (w.r.t. prime meredian): %f", o->com_x);
    printf("\n3.Centre of mass y coordinate (w.r.t. equator): %f", o->com_y);
    printf("\n4.Centre of mass z coordinate (w.r.t. sea level): %f", o->com_z);
    printf("\n5.Mass of system : %f", o->mass);
    printf("\n--------------------------------------------------------------------");
    printf("\nPoint at which we testing Gravitional Force applied by the system is as follows : ");
    printf("\n(x, y, z) = (0, 0, 100) & mass of earth = (5.97 X 10^24) Kg");
    
    fscanf(f, "%f", &xtest);
    fscanf(f, "%f", &ytest);
    fscanf(f, "%f", &ztest);
    fscanf(f, "%f", &mtest);
    if((ytest > 90) || (ytest < -90) || (xtest > 179) || (xtest < -179) || (ztest < 100) || (mtest < 1)){
        printf("\nInvalid Test Body!");
        return;
    }
    //Convert Latitude & Longitude to Km
    ytest1 = convert_latitude(ytest);
    xtest1 = convert_longitude(xtest);
    BarnesHut3D_force_calculate(o, xtest1, ytest1, ztest, mtest);
    printf("\nProgram Ended!");
    printf("\n--------------------------------------------------------------------");
    BarnesHut3D_destroy_tree(o);
    exit(0);
    return;
}

//2. charges() :
void charge(char *filename){
    float x, y, c;
    //Following Variables are system bounds
    float xlow, xhigh, ylow, yhigh;
    //Following Variables are test points for force
    float xtest, ytest, ctest;
    //size variable is number of nodes mentioned in text files
    int size;
    //Memory is allocated
    quadtree *q = malloc(sizeof(quadtree));
    //If memory doesn't exist or unreachable
    if (!q)
        return;
    //FRONT END
    printf("\n--------------------------------------------------------------------");
    printf("\n The following test system is built with charges in 2D example:");
    printf("\nNOTE: All values are w.r.t. a constant time in order to get accurate results");
    printf("\n--------------------------------------------------------------------");
    printf("\nThe system bounds have been set as follows for test purposes : ");
    printf("\nx & y (-10 to 10)");
    printf("\n--------------------------------------------------------------------");
    FILE *f;
    f = fopen(filename, "r");
    if(f == NULL) {
        printf("File can't open");
        return;
    }
    
    fscanf(f, "%f", &xlow);
    fscanf(f, "%f", &ylow);
    fscanf(f, "%f", &xhigh);
    fscanf(f, "%f", &yhigh);
    if((xlow == xhigh) && (ylow == yhigh)){
        printf("\nInvalid System bounds!");
        return;
    }
    
    //System bounds must be positively & negatively greater than the system
    q = BarnesHut2D_init(xlow, ylow, xhigh, yhigh);
    
    fscanf(f, "%d", &size);
    for(int i = 0; i < size; i++){
        fscanf(f, "%f", &x);
        fscanf(f, "%f", &y);
        fscanf(f, "%f", &c);
        BarnesHut2D_insert(q, x, y, c);
    }
    printf("\n1.Total Number of charges added to system: %d", q->leaves);
    printf("\n--------------------------------------------------------------------");
    printf("\nThe system is built as follows : \n");
    BarnesHut2D_display(q);
    printf("\n--------------------------------------------------------------------");
    BarnesHut2D_tree_calculate(q);
    printf("\n2.Centre of mass x coordinate : %f", q->com_x);
    printf("\n3.Centre of mass y coordinate : %f", q->com_y);
    printf("\n4.Charge of system : %f", q->charge);
    printf("\n--------------------------------------------------------------------");
    printf("\nPoint at which we testing Force applied by the system is as follows : ");
    printf("\n(x, y) = (0, 0) & unit positive charge");
    
    fscanf(f, "%f", &xtest);
    fscanf(f, "%f", &ytest);
    fscanf(f, "%f", &ctest);
    BarnesHut2D_force_calculate(q, xtest, ytest, ctest);
    
    printf("\nProgram Ended!");
    printf("\n--------------------------------------------------------------------");
    BarnesHut2D_destroy_tree(q);
    exit(0);
    return;
}

/*3. convert_latitude() & convert_longitude() 
Convert Latitude & Longitude to Km*/

float convert_latitude(float y){
    //distance between 2 latitudes is 110kms
    return 110*y;
}

float convert_longitude(float x){
    //distance between longitudes changes from equator to earth avg is 85 kms @ 40N or 40S
    return 85*x;
}
