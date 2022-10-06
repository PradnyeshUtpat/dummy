
#include <stdio.h>
#include <stdlib.h>


typedef struct quadtree{
    struct quadtree* child[4];
    int leaves; 
    
    
    float com_x;
    float com_y;
    
    float charge;
    
    
    float bound_bottom_x;
    float bound_bottom_y;

    float bound_mid_x;
    float bound_mid_y;

    float bound_top_x;
    float bound_top_y;
} quadtree;



quadtree* BarnesHut2D_init(float x1, float y1, float x2, float y2);



void BarnesHut2D_destroy_tree(quadtree *root);



int BarnesHut2D_insert(quadtree *root, float x, float y, float c);



int BarnesHut2D_subtree_insert(quadtree *root, float x, float y, float c);



void BarnesHut2D_tree_calculate(quadtree *root);



int BarnesHut2D_force_calculate(quadtree *root, float x, float y, float charge);



void BarnesHut2D_display(quadtree *root);