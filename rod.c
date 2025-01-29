#include <stdio.h>
#include <stdlib.h>
#include "rod.h"

// Returns total value from piece
void evaluate_piece(const piece_t *piece, int rod_length) {
    if (piece->length <= rod_length) {
        int count = rod_length / piece->length;
        int value = count * piece->value;
        printf("%d @ %d = %d\n", count, piece->length, value);
    }
}

// Returns index value containing best piece
int find_best_piece(const piece_t *pieces, int piece_count, int rod_length) {
    int best_index = -1;
    int best_value = 0;
    
    for (int ix = 0; ix < piece_count; ix++) {
        if (pieces[ix].length <= rod_length) {
            int count = rod_length / pieces[ix].length;
            int value = count * pieces[ix].value;
            if (value > best_value) {
                best_value = value;
                best_index = ix;
            }
        }
    }
    
    return best_index;
}

// Returns value from cutting with best piece
int process_rod_cutting(int rod_length, piece_t *pieces, int piece_count) {
    int best_index = find_best_piece(pieces, piece_count, rod_length);
    
    if (best_index == -1) {
        return 0;
    }
    
    int count = rod_length / pieces[best_index].length;
    int value = count * pieces[best_index].value;
    printf("%d @ %d = %d\n", count, pieces[best_index].length, value);
    
    int remainder = rod_length - (count * pieces[best_index].length);
    if (remainder > 0) {
        printf("Remainder: %d\n", remainder);
    }
    
    return value;
}

// Take user input and convert to piece data
// Returns number of pieces processed
int read_pieces(piece_t *pieces) {
    int piece_count = 0;
    int length, value;
    
    while (piece_count < MAX_PIECES && scanf("%d, %d", &length, &value) == 2) {
        if (length < MIN_LENGTH || length > MAX_LENGTH) {
            continue;
        }
        pieces[piece_count].length = length;
        pieces[piece_count].value = value;
        piece_count++;
    }
    
    return piece_count;
}