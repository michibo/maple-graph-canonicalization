
# Use this to define the canonical_labeling function in maple:

canonical_labeling := define_external('canonical_labeling', \
colored_edges::(ARRAY(1..3*m, integer[4])), \ # colored edges as array
\ # Format: ( va_1, vb_1, w_1, va_2, vb_2, w_2, ... )
\ # For a graph with edges (va_k, vb_k) having colors w_k.
ext_vertices::(ARRAY(1..l,integer[4])), \ # external vertices
\ # Array of vertices with another color ( ve_1, ve_2, ... )
lab::(ARRAY(1..n,integer[4])), \ # canonical labeling returned
\ # Canonical labelling is written into this. 
n::(integer[4]), \ # number of vtcs
m::(integer[4]), \ # number of edges
w::(integer[4]), \ # number of colors
l::(integer[4]), \ # number of ext vertices
LIB="nauty_wrapper.so" ):

# Example:

lab:=Array([0,1,2,3,4],datatype=integer[4]):
ext:=Array([4],datatype=integer[4]):

G:=Array([0,3,0, 0,2,0, 2,1,0, 3,1,0, 3,4,0], datatype=integer[4]):

canonical_labeling(G, ext, lab, 5, 5, 1, 1);

lab;

G:=Array(subs([1=2,2=3,3=4,4=1],[0,3,0, 0,2,0, 2,1,0, 3,1,0, 3,4,0]), datatype=integer[4]):

canonical_labeling(G, ext, lab, 5, 5, 1, 1);

lab;
