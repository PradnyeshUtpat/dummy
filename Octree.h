
#include <stdio.h>
#include <stdlib.h>

typedef struct octree{
    struct octree* child[8];
    int leaves; 
    
    
    float com_x;
    float com_y;
    float com_z;
    
    
    float mass;
    
    
    float bound_bottom_x;
    float bound_bottom_y;
    float bound_bottom_z;
    
    float bound_mid_x;
    float bound_mid_y;
    float bound_mid_z;
    
    float bound_top_x;
    float bound_top_y;
    float bound_top_z;
} octree;



octree* BarnesHut3D_init(float x1, float y1, float z1, float x2, float y2, float z2);



void BarnesHut3D_destroy_tree(octree *root);



int BarnesHut3D_insert(octree *root, float x, float y, float z, float m);



int BarnesHut3D_subtree_insert(octree *root, float x, float y, float z, float m);



void BarnesHut3D_tree_calculate(octree *root);


int BarnesHut3D_force_calculate(octree *root, float x, float y, float z, float mass);



void BarnesHut3D_display(octree *root);