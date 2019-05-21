
// Test program to get a canonical labelling from nauty for a graph with colored edges.
// 
// by Michael Borinsky 2018

#include <stdio.h>

int canonical_labeling( const int* colored_edges, const int* ext_vertices, int* labeling, int num_vertices, int num_edges, int num_colors, int num_ext_vertices );

int main()
{
    const int num_vertices = 5;
    const int num_edges = 5;
    const int num_colors = 1;
    const int num_ext_vertices = 1;

    int lab[] = { 0, 1, 2, 3, 4 };
    int ilab[num_vertices];
    int colored_edges[] = { 0,1,1, 1,2,0, 2,3,1, 3,0,1, 0,4,0 };
    int ext_vertices[] = { 4 };

    for( int k = 0; k < num_vertices; k++ )
    {
        ilab[lab[k]] = k;
    }


    for( int k = 0; k < num_edges; k++ )
    {
        colored_edges[3*k+0] = ilab[colored_edges[3*k+0]];
        colored_edges[3*k+1] = ilab[colored_edges[3*k+1]];
    }

    for( int k = 0; k < num_ext_vertices; k++ )
    {
        ext_vertices[k] = ilab[ext_vertices[k]];
    }

    canonical_labeling( colored_edges, ext_vertices, lab, num_vertices, num_edges, num_colors, num_ext_vertices );

    for( int k = 0; k < num_vertices; k++ )
    {
        printf("%d - %d\n", k, lab[k]);
    }

    return 0;
}
