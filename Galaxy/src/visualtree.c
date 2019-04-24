#include "../headers/visualtree.h"
#include <stdio.h>
#include <stdlib.h>


FILE* write_begin(char *name) {
  FILE *f = fopen(name, "w");
  fprintf(f, "digraph tree {\n");
  fprintf(f, "  splines=false\n");
  fprintf(f, "  node [shape=record,height=.1]\n");
  fprintf(f, "  edge [tailclip=false, arrowtail=dot, dir=both];\n\n");
  return f;
}


void write_end(FILE *f) {
  fprintf(f, "\n}\n");
  fclose(f);
}


void write_node(FILE *f, BodyNode *B) {
  fprintf(f, "  n%p [label=\" <value>\"];\n", B);
}

void write_leaf_empty(FILE *f, BodyNode *B) {

  fprintf(f, "  n%p [label=\" <value> \" color=green];\n", B);
}

void write_leaf_not_empty(FILE *f, BodyNode *B) {

    printf("test\n" );
  fprintf(f, "  n%p [label=\" <value> * \"color=green];\n", B);
}

void write_leaf_debug_add_leaf(BodyNode *B) {



    /*fprintf(f, "  n%p [label=\" <value> * \"color=blue];\n", B);*/
}

void write_child_link(FILE *f, BodyNode *B) {

  fprintf(f, "  n%p:value:c -> n%p:value[arrowtail=\"none\",arrowhead=\"none\"];\n", B, B->northWest);
  fprintf(f, "  n%p:value:c -> n%p:value[arrowtail=\"none\",arrowhead=\"none\"];\n", B, B->northEast);
  fprintf(f, "  n%p:value:c -> n%p:value[arrowtail=\"none\",arrowhead=\"none\"];\n", B, B->southWest);
  fprintf(f, "  n%p:value:c -> n%p:value[arrowtail=\"none\",arrowhead=\"none\"];\n", B, B->southEast);

}




void write_tree_aux(FILE *f, BodyNode *B)
{

    if (B==NULL)
        return;

    if (B->northWest==NULL && B->body != NULL)
    {
        printf("test\n" );
        write_leaf_not_empty(f,B);
    }
    else if(B->northWest==NULL && B->body == NULL)
    {

        printf("testzer\n" );
        write_leaf_empty(f,B);
    }
    else
    {
        write_node(f,B);
    }


    if (B->northWest!=NULL||B->northEast!=NULL||B->southWest!=NULL||B->southEast!=NULL)
    {

        write_child_link(f,B);

        write_tree_aux(f,B->northWest);
        write_tree_aux(f,B->northEast);
        write_tree_aux(f,B->southEast);
        write_tree_aux(f,B->southWest);

    }

}


void write_tree(BodyNode *B) {



  FILE *f;
  f = write_begin("current-tree.dot");
  write_tree_aux(f, B);


  write_end(f);
  system("dot -Tps2 current-tree.dot | ps2pdf - - > current-tree.pdf");
}
