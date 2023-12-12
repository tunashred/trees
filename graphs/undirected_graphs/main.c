#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 8

typedef struct Graph {
    int distance_matrix[SIZE][SIZE];
    int nodes[SIZE];
    int used_nodes;
} Graph;

void init_graph(Graph *graph, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            graph->distance_matrix[i][j] = 0;
        }
        graph->nodes[i] = -1;
    }

    graph->used_nodes = 0;
}

void insert_node(int position, Graph *graph) {
    if(position >= SIZE || graph->used_nodes > SIZE) {
        printf("Error.\n");
        return;
    }

    graph->nodes[position] = position;
    (graph->used_nodes)++;
}

void insert_arc(int from, int to, int value, Graph *graph) {
    if(from >= SIZE || to >= SIZE || from < 0 || to < 0) {
        printf("Index out of bounds\n");
        return;
    }

    graph->distance_matrix[from][to] = value;
    graph->distance_matrix[to][from] = value;
}

void print_graph(Graph *graph) {
    printf("\t   ");
    for(int i = 0; i < SIZE; i++) {
        printf("%-5d", graph->nodes[i]);
    }
    printf("\n");

    for(int i = 0; i < SIZE + SIZE * 5 - 5; i++) {
        printf("-");
    }
    printf("\n");

    for(int i = 0; i < SIZE; i++) {
        printf("%-2d  |  ", graph->nodes[i]);
        for(int j = 0; j < SIZE; j++) {
            printf("%-5d", graph->distance_matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
}

void delete_node(int position, Graph *graph) {
    graph->nodes[position] = -1;

    for(int i = 0; i < SIZE; i++) {
        graph->distance_matrix[i][position] = 0;
        graph->distance_matrix[position][i] = 0;
    }

    (graph->used_nodes)--;
}

void delete_arc(int from, int to, Graph *graph) {
    if(from >= SIZE || to >= SIZE) {
        printf("Index out of bounds\n");
        return;
    }

    graph->distance_matrix[from][to] = -1;
    graph->distance_matrix[to][from] = -1;
}

bool any_nodes_left(bool nodes[]) {
    for(int i = 0; i < SIZE; i++) {
        if(!nodes[i]) {
            return true;
        }
    }

    return false;
}

void prim(Graph *graph, Graph *mst) {
    init_graph(mst, SIZE);
    for(int i = 0; i < SIZE; i++) {
        insert_node(i, mst);
    }

    int current_node = 3;
    int next_node, min;

    bool *added_nodes = calloc(mst->used_nodes, sizeof *added_nodes);
    added_nodes[current_node] = true;

    while(any_nodes_left(added_nodes)) {
        min = (1 << 30);

        for(int j = mst->used_nodes - 1; j >= 0; j--) {
            if(added_nodes[j]) {
                for(int i = mst->used_nodes - 1; i >= 0; i--) {
                    int current_arc = graph->distance_matrix[i][j];
                    if(current_arc != 0 && current_arc < min && !added_nodes[i]) {
                        min = current_arc;
                        current_node = j;
                        next_node = i;
                    }
                }
            }
        }

        if(current_node != next_node) {
            insert_arc(current_node, next_node, min, mst);
            current_node = next_node;
            added_nodes[current_node] = true;
        }
        else {
            for(int i = 0; i < graph->used_nodes; i++) {
                if(!added_nodes[i]) {
                    current_node = i;
                    break;
                }
            }
        }
    }

    free(added_nodes);
}

int main() {
    srand(time(NULL));

    Graph graph;
    init_graph(&graph, SIZE);

    insert_node(0, &graph);
    insert_node(1, &graph);
    insert_node(2, &graph);
    insert_node(3, &graph);
    insert_node(4, &graph);
    insert_node(4, &graph);
    insert_node(5, &graph);
    insert_node(6, &graph);
    insert_node(7, &graph);

    insert_arc(0, 1, 4 , &graph);
    insert_arc(0, 6, 9 , &graph);
    insert_arc(0, 3, 16, &graph);
    insert_arc(1, 2, 20, &graph);
    insert_arc(1, 6, 8 , &graph);
    insert_arc(2, 4, 4 , &graph);
    insert_arc(3, 5, 14, &graph);
    insert_arc(3, 4, 5 , &graph);
    insert_arc(3, 7, 6 , &graph);
    insert_arc(4, 6, 12, &graph);
    insert_arc(4, 7, 3 , &graph);
    insert_arc(6, 5, 6 , &graph);
    insert_arc(6, 7, 13, &graph);

    print_graph(&graph);

    Graph mst;

    prim(&graph, &mst);

    print_graph(&mst);

    return 0;
}
