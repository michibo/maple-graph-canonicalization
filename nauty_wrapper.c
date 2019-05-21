
// Program to get a canonical labelling from nauty for a graph with colored edges.
// 
// by Michael Borinsky 2018

#include <assert.h>

#include <nausparse.h>

// Important: Colors and vertices must be numbered 0,1,2,3,4...
// There must be at least one color.

// This function is going to be called by maple:
extern int canonical_labeling( 
    const int* colored_edges, // Array of edges in the format [v0,v1,w], 
                               // where v0 and v1 are the vertices which 
                               // the edge connects and w is the edge color. 
    const int* ext_vertices,   // Array of external vertices (vertices with a 
                               // different color).
    int* labeling,             // Output: Canonical label of the vertices.
    int num_vertices, int num_edges, int num_colors, int num_ext_vertices )
{
    if( num_vertices <= 0 )
        return 0;

    assert( num_colors > 0 && "canonical_labeling needs num_colors > 0" );
    if( num_colors <= 0)
        return -1;

    DYNALLSTAT( int, lab, lab_sz );
    DYNALLSTAT( int, ptn, ptn_sz );
    DYNALLSTAT( int, orbits, orbits_sz );

    static DEFAULTOPTIONS_SPARSEDIGRAPH(options);
    statsblk stats;

    SG_DECL( sg );
    SG_DECL( cg );

    options.getcanon = TRUE;
    options.defaultptn = FALSE;

    int V = num_vertices + num_edges + num_colors + num_ext_vertices;  
    // number of vertices of simple graph w/o colors

    int E = 3*num_edges + num_ext_vertices;
    // number of directed edges of simple graph w/o colors

    // Initialize nauty:
    SG_INIT( sg );
    SG_INIT( cg );

    int m = SETWORDSNEEDED( V );
    nauty_check( WORDSIZE, m, V, NAUTYVERSIONID );

    DYNALLOC1( int, lab, lab_sz, V, "malloc" );
    DYNALLOC1( int, ptn, ptn_sz, V, "malloc" );
    DYNALLOC1( int, orbits, orbits_sz, V, "malloc" );

    SG_ALLOC( sg, V, E, "malloc" );

    sg.nv = V;
    sg.nde = E;
   
    memset(sg.v, 0, sizeof(int) * (num_vertices + num_colors) );
    memset(sg.d, 0, sizeof(int) * (num_vertices + num_colors) );

    // Start with a trivial labeling 
    for( int k = 0; k < V; k++ )
        lab[k] = k;

    for( int k = 0; k < num_vertices-1; k++ )
        ptn[k] = 1;

    ptn[num_vertices-1] = 0;

    // and add a new class of vertices for each color:
    int colors_offset = num_vertices;
    for( int k = 0; k < num_colors; k++ )
        ptn[colors_offset+k] = 0;

    // We also add a new vertex for each edge. Each edge vertex is connected to 
    // the `color-vertex' to which it belongs.
    int edges_offset = colors_offset + num_colors;
    for( int k = 0; k < num_edges; k++ )
    {
        sg.v[edges_offset+k] = 3*k;
        sg.d[edges_offset+k] = 3;
        ptn [edges_offset+k] = 1;

        sg.e[3*k+0] = colored_edges[3*k+0];
        sg.e[3*k+1] = colored_edges[3*k+1];
        sg.e[3*k+2] = colors_offset + colored_edges[3*k+2];
    }

    ptn[edges_offset+num_edges-1] = 0;

    // Also add the external vertices:
    int ext_offset = edges_offset + num_edges;
    for( int k = 0; k < num_ext_vertices; k++ )
    {
        sg.v[ext_offset+k] = 3*num_edges + k;
        sg.d[ext_offset+k] = 1;
        sg.e[3*num_edges + k] = ext_vertices[k];

        ptn[ext_offset+k] = 1;
    }

    ptn[ext_offset+num_ext_vertices-1] = 0;

    // Run nauty:
    sparsenauty( &sg, lab, ptn, orbits, &options, &stats, &cg );

    SG_FREE( sg );
    SG_FREE( cg );

    for( int k = 0; k < num_vertices; k++ )
        labeling[k] = lab[k];

    DYNFREE( lab, lab_sz );
    DYNFREE( ptn, ptn_sz );
    DYNFREE( orbits, orbits_sz );
}

