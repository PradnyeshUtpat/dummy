
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Quadtree.h"


quadtree* BarnesHut2D_init(float x1, float y1, float x2, float y2){
    
    quadtree* root = malloc(sizeof(quadtree));
    if (!root)
        return NULL;
    
    
    root->bound_bottom_x = (x1 < x2 ? x1 : x2);
    root->bound_bottom_y = (y1 < y2 ? y1 : y2);
    root->bound_top_x = (x1 < x2 ? x2 : x1);
    root->bound_top_y = (y1 < y2 ? y2 : y1);
    root->bound_mid_x = (x1 + x2) / 2;
    root->bound_mid_y = (y1 + y2) / 2;
    
    
    root->com_x = 0;
    root->com_y = 0;
    root->charge = 0;
    
    
    for (int i = 0; i < 4; i++)
        root->child[i] = NULL;

    root->leaves = 0;
    return root;
}


void BarnesHut2D_destroy_tree(quadtree *root){
   
    if (!root) 
        return;
    
    for (int i = 0; i < 4; i++)
        BarnesHut2D_destroy_tree(root->child[i]);
    free(root);
}


int BarnesHut2D_insert(quadtree *root, float x, float y, float c){
    if (!root) 
        return 0;
    
    if (root->leaves == 0) {
        root->com_x = x;
        root->com_y = y;
        root->charge = c;
    }
    
    else {
        
        if (root->leaves == 1) {
            BarnesHut2D_subtree_insert(root, root->com_x, root->com_y, root->charge);
        }
        
        BarnesHut2D_subtree_insert(root, x, y, c);
    }
   
    (root->leaves)++;
    return (root->leaves);
}


int BarnesHut2D_subtree_insert(quadtree *root, float x, float y, float c){
    if (!root) 
        return 0;
    
    int quadrant = 0;
    float min_x, min_y;
    float max_x, max_y;
    if (x > root->bound_mid_x) {
        quadrant += 1;
        min_x = root->bound_mid_x;
        max_x = root->bound_top_x;
    } 
    else {
        min_x = root->bound_bottom_x;
        max_x = root->bound_mid_x;
    }
    if (y > root->bound_mid_y) {
        quadrant += 2;
        min_y = root->bound_mid_y;
        max_y = root->bound_top_y;
    } 
    else {
        min_y = root->bound_bottom_y;
        max_y = root->bound_mid_y;
    }
    
    if (!root->child[quadrant])
        root->child[quadrant] = BarnesHut2D_init(min_x, min_y, max_x, max_y);
    
    return BarnesHut2D_insert(root->child[quadrant], x, y, c);
}


void BarnesHut2D_tree_calculate(quadtree *root){
    
    if (!root) 
        return;
    
    if (root->leaves == 1)
        return;
    
    root->charge = 0;
    root->com_x = 0;
    root->com_y = 0;

    for (int i = 0; i < 4; i++) {
        
        if (!root->child[i])
            continue;
        
        BarnesHut2D_tree_calculate(root->child[i]);

        float child_charge = root->child[i]->charge;
        root->charge += child_charge;
        
        root->com_x += child_charge * (root->child[i]->com_x);
        root->com_y += child_charge * (root->child[i]->com_y);
    }
   
    root->com_x /= root->charge;
    root->com_y /= root->charge;
}


int BarnesHut2D_force_calculate(quadtree *root, float x, float y, float charge){
    if (!root)
        return 0;
   
    float fx, fy, fR;
    fx = fy = fR = 0;
   
    float rad = sqrtf(powf(x - root->com_x, 2) + powf(y - root->com_y, 2));
    printf("\n5.Radius of calculaton : %f", rad);
    
    if (rad == 0) 
        return 0;
    float r3 = powf(rad, 3);
    
    fx = 9e9F * charge * root->charge * (x - root->com_x) / r3;
    fy = 9e9F * charge * root->charge * (y - root->com_y) / r3;
    printf("\n6.Force on body in x direction : %f", fx);
    printf("\n7.Force on body in y direction : %f", fy);
    
   
    fR = sqrtf(powf(fx, 2) + powf(fy, 2));
    printf("\n8.Resultant Force on body  : %f", fR);
    return 1;
}


void BarnesHut2D_display(quadtree *root){
    
    if (!root)
        return;
    for(int i = 0; i < 4; i++){
        
        if(!root->child[i])
            continue;
        printf("X:%f", root->child[i]->com_x);
        printf("  Y:%f", root->child[i]->com_y);
        printf("  Charge:%f\n", root->child[i]->charge);
        
        
        BarnesHut2D_display(root->child[i]);
    }
    return;
}
