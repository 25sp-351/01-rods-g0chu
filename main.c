#include <stdio.h>
#include <stdlib.h>
#include "rod.h"

int main(int argc, char *argv[]) {
    // Handle if invalid arguments
    if (argc != 2) {
        printf("Usage: %s <rod_length>\n", argv[0]);
        return 1;
    }

    int rod_length = atoi(argv[1]);
    piece_t pieces[MAX_PIECES];
    int piece_count = read_pieces(pieces);
    
    if (piece_count == 0) {
        printf("No valid pieces inputted.\n");
        return 1;
    }

    process_rod_cutting(rod_length, pieces, piece_count);

    return 0;
}