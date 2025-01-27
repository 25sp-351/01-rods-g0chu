#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "rod.h"

// Test helper functions
FILE* original_stdout;

void redirect_stdout() {
    fflush(stdout);
    original_stdout = stdout;
    stdout = fopen("test_output.txt", "w");
}

void reset_stdout() {
    fflush(stdout);
    fclose(stdout);
    stdout = original_stdout;
}

char* read_test_output() {
    static char buffer[1024];
    FILE* f = fopen("test_output.txt", "r");
    memset(buffer, 0, sizeof(buffer));
    size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, f);
    buffer[bytes_read] = '\0';
    fclose(f);
    return buffer;
}

// Test normal cases
void test_normal_cases() {
    printf("Testing normal cases...\n");
    piece_t test_pieces[] = {
        {5, 10},
        {10, 20},
        {20, 50}
    };
    
    // Case 1: Perfect fit (rod length 20)
    redirect_stdout();
    int total_value = process_rod_cutting(20, test_pieces, 3);
    reset_stdout();
    char* output = read_test_output();
    assert(strstr(output, "1 @ 20 = 50") != NULL);
    assert(total_value == 50);
    printf("Case 1: ✓\n");
    
    // Case 2: Multiple cuts of same length (rod length 40)
    redirect_stdout();
    total_value = process_rod_cutting(40, test_pieces, 3);
    reset_stdout();
    output = read_test_output();
    assert(strstr(output, "2 @ 20 = 100") != NULL);
    assert(total_value == 100);
    printf("Case 2: ✓\n");
    
    // Case 3: Multiple cuts of smallest piece (rod length 35)
    redirect_stdout();
    total_value = process_rod_cutting(35, test_pieces, 3);
    reset_stdout();
    output = read_test_output();
    assert(strstr(output, "7 @ 5 = 70") != NULL);
    assert(total_value == 70);
    printf("Case 3: ✓\n");
}

// Test edge cases
void test_edge_cases() {
    printf("Testing edge cases...\n");
    piece_t test_pieces[] = {
        {5, 10},
        {10, 20},
        {20, 50}
    };
    
    // Case 1: Minimum useful rod length
    redirect_stdout();
    int total_value = process_rod_cutting(5, test_pieces, 3);
    reset_stdout();
    char* output = read_test_output();
    assert(strstr(output, "1 @ 5 = 10") != NULL);
    assert(total_value == 10);
    printf("Case 1: ✓\n");
    
    // Case 2: Large rod length
    redirect_stdout();
    total_value = process_rod_cutting(100, test_pieces, 3);
    reset_stdout();
    output = read_test_output();
    assert(strstr(output, "5 @ 20 = 250") != NULL);
    assert(total_value == 250);
    printf("Case 2: ✓\n");
    
    // Case 3: Rod smaller than any piece
    redirect_stdout();
    total_value = process_rod_cutting(3, test_pieces, 3);
    reset_stdout();
    assert(total_value == 0);
    printf("Case 3: ✓\n");
}

// Test invalid input
void test_invalid_input() {
    printf("Testing invalid input...\n");
    
    // Case 1: Empty piece array
    piece_t test_pieces[] = {
        {5, 10},
        {10, 20},
        {20, 50}
    };
    redirect_stdout();
    int result = process_rod_cutting(10, test_pieces, 0);
    reset_stdout();
    assert(result == 0);
    printf("Case 1: ✓\n");
}

int main() {
    printf("Starting tests\n");
    printf("==============\n");
    
    test_normal_cases();
    test_edge_cases();
    test_invalid_input();
    
    printf("All tests completed successfully!\n");
    remove("test_output.txt");
    
    return 0;
}