# maple-graph-canonicalization

Very simple maple plugin that uses Brendan McKay's nauty to canonicalize (edge-colored) graphs.

It uses *nauty* for the actual graph canonicalization. [McKay, B.D. and Piperno, A., Practical Graph Isomorphism, II, Journal of Symbolic Computation, 60 (2014), pp. 94-112](http://dx.doi.org/10.1016/j.jsc.2013.09.003)

Installation
============

Just call 

~~~~
make
~~~~

to download nauty from http://pallini.di.uniroma1.it/, compile it and also compile the plugin.

Maple
=====

The file script.mpl contains a working example. Briefly, use

Use the command 

~~~~
canonical_labeling := define_external('canonical_labeling', \
colored_edges::(ARRAY(1..3*m, integer[4])), \ 
\ # colored edges as array
\ # Format: ( va_1, vb_1, w_1, va_2, vb_2, w_2, ... )
\ # For a graph with edges (va_k, vb_k) having colors w_k.
ext_vertices::(ARRAY(1..l,integer[4])), \ 
\ # external vertices
\ # Array of vertices with another color ( ve_1, ve_2, ... )
lab::(ARRAY(1..n,integer[4])), \ 
\ # canonical labeling returned
\ # Canonical labelling is written into this. 
n::(integer[4]), \ # number of vtcs
m::(integer[4]), \ # number of edges
w::(integer[4]), \ # number of colors
l::(integer[4]), \ # number of ext vertices
LIB="nauty_wrapper.so" ):
~~~~

to include the wrapper into maple. The role of the parameters is explained in the comments.

Usage Example
=============

~~~~
lab:=Array([0,1,2,3,4],datatype=integer[4]):
ext:=Array([4],datatype=integer[4]):

G:=Array([0,3,0, 0,2,0, 2,1,0, 3,1,0, 3,4,0], datatype=integer[4]):

canonical_labeling(G, ext, lab, 5, 5, 1, 1);

lab;

G:=Array(subs([1=2,2=3,3=4,4=1],[0,3,0, 0,2,0, 2,1,0, 3,1,0, 3,4,0]), datatype=integer[4]):

canonical_labeling(G, ext, lab, 5, 5, 1, 1);

lab;
~~~~
