
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Octree.h"


octree* BarnesHut3D_init(float x1, float y1, float z1, float x2, float y2, float z2){
    
    octree* root = malloc(sizeof(octree));
    if (!root)
        return NULL;
    
    
    root->bound_bottom_x = (x1 < x2 ? x1 : x2);
    root->bound_bottom_y = (y1 < y2 ? y1 : y2);
    root->bound_bottom_z = (z1 < z2 ? z1 : z2);
    root->bound_top_x = (x1 < x2 ? x2 : x1);
    root->bound_top_y = (y1 < y2 ? y2 : y1);
    root->bound_top_z = (z1 < z2 ? z2 : z1);
    root->bound_mid_x = (x1 + x2) / 2;
    root->bound_mid_y = (y1 + y2) / 2;
    root->bound_mid_z = (z1 + z2) / 2;
    
    
    root->com_x = 0;
    root->com_y = 0;
    root->com_z = 0;
    root->mass = 0;
    
    
    for (int i = 0; i < 8; i++)
        root->child[i] = NULL;
    
    root->leaves = 0;
    return root;
}


void BarnesHut3D_destroy_tree(octree *root) {
    
    if (!root) 
        return;
    
    for (int i = 0; i < 8; i++)
        BarnesHut3D_destroy_tree(root->child[i]);
    free(root);
}


int BarnesHut3D_insert(octree *root, float x, float y, float z, float m){
    if (!root) 
        return 0;
    
    if (root->leaves == 0) {
        root->com_x = x;
        root->com_y = y;
        root->com_z = z;
        root->mass = m;
    }
    
    else {
        
        if (root->leaves == 1) {
            BarnesHut3D_subtree_insert(root, root->com_x, root->com_y, root->com_z, root->mass);
        }
        
        BarnesHut3D_subtree_insert(root, x, y, z, m);
    }
    
    (root->leaves)++;
    return (root->leaves);
}


int BarnesHut3D_subtree_insert(octree *root, float x, float y, float z, float m) {
    if (!root) 
        return 0;
    
    int octant = 0;
    float min_x, min_y, min_z;
    float max_x, max_y, max_z;
    if (x > root->bound_mid_x) {
        octant += 1;
        min_x = root->bound_mid_x;
        max_x = root->bound_top_x;
    } 
    else {
        min_x = root->bound_bottom_x;
        max_x = root->bound_mid_x;
    }
    if (y > root->bound_mid_y) {
        octant += 2;
        min_y = root->bound_mid_y;
        max_y = root->bound_top_y;
    } 
    else {
        min_y = root->bound_bottom_y;
        max_y = root->bound_mid_y;
    }
    if (z > root->bound_mid_z) {
        octant += 4;
        min_z = root->bound_mid_z;
        max_z = root->bound_top_z;
    } 
    else {
        min_z = root->bound_bottom_z;
        max_z = root->bound_mid_z;
    }
    
    if (!root->child[octant])
        root->child[octant] = BarnesHut3D_init(min_x, min_y, min_z, max_x, max_y, max_z);
    
    return BarnesHut3D_insert(root->child[octant], x, y, z, m);
}


void BarnesHut3D_tree_calculate(octree *root){
    
    if (!root) 
        return;
    
    if (root->leaves == 1)
        return;
    
    root->mass = 0;
    root->com_x = 0;
    root->com_y = 0;
    root->com_z = 0;

    for (int i = 0; i < 8; i++) {
        
        if (!root->child[i])
            continue;
        
        
        BarnesHut3D_tree_calculate(root->child[i]);

        float child_mass = root->child[i]->mass;
        root->mass += child_mass;
        
        root->com_x += child_mass * (root->child[i]->com_x);
        root->com_y += child_mass * (root->child[i]->com_y);
        root->com_z += child_mass * (root->child[i]->com_z);
    }
    
    root->com_x /= root->mass;
    root->com_y /= root->mass;
    root->com_z /= root->mass;
}


int BarnesHut3D_force_calculate(octree *root, float x, float y, float z, float mass){
    if (!root)
        return 0;
    
    float fx, fy, fz, fR;
    fx = fy = fz = fR = 0;
    
    float rad = sqrtf(powf(x - root->com_x, 2) + powf(y - root->com_y, 2) + powf(z - root->com_z, 2));
    printf("\n6.Radius of calculaton : %f", rad);
    
    if (rad == 0) 
        return 0;
    float r3 = powf(rad, 3);
    
    fx = 6.672e-11F * mass * root->mass * (x - root->com_x) / r3;
    fy = 6.672e-11F * mass * root->mass * (y - root->com_y) / r3;
    fz = 6.672e-11F * mass * root->mass * (z - root->com_z) / r3;
    printf("\n7.Force on body in x direction : %f", fx);
    printf("\n8.Force on body in y direction : %f", fy);
    printf("\n9.Force on body in z direction : %f", fz);
    
    
    fR = sqrtf(powf(fx, 2) + powf(fy, 2) + powf(fz, 2));
    printf("\n10.Resultant Force on body  : %f", fR);
    return 1;
}


void BarnesHut3D_display(octree *root){
    
    if (!root)
        return;
    for(int i = 0; i < 8; i++){
        
        if(!root->child[i])
            continue;
        printf("Latitude:%f", root->child[i]->com_x);
        printf("  Longitude:%f", root->child[i]->com_y);
        printf("  Altitude:%f", root->child[i]->com_z);
        printf("  Mass:%f\n", root->child[i]->mass);
        
        // Use of recursion 
        BarnesHut3D_display(root->child[i]);
    }
    return;
}
