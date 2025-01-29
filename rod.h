#ifndef ROD_H
#define ROD_H

#define MAX_PIECES 100
#define MAX_LENGTH 1000
#define MIN_LENGTH 1

typedef struct {
    int length;
    int value;
} piece_t;

// Function prototypes
void evaluate_piece(const piece_t *piece, int rod_length);
int find_best_piece(const piece_t *pieces, int piece_count, int remaining_length);
int process_rod_cutting(int rod_length, piece_t *pieces, int piece_count);
int read_pieces(piece_t *pieces);

#endif