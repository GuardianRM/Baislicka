#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <assert.h>

#define ENGINE_NAME "Baislicka"
#define ENGINE_VERSION "2.0"
#define ENGINE_AUTHOR "Twipply"
#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define TEST1_FEN "k7/5n2/8/8/5R2/8/3b1P2/K7 w - - 0 0"
#define TEST2_FEN "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define TEST3_FEN "8/3K4/8/3k4/8/8/8/7N w - - 0 0"
#define TEST4_FEN "8/1kp1p3/6N1/4B3/8/8/R3K2R/8 w - - 0 0"
#define SETBIT(x, n) ((x) = (x) | ((uint64_t)1<<(n)))
#define GETBIT(x, n) (((x)>>(n))&1)
#define MAX_MOVES 256
#define MAX_DEPTH 32
#define POS_TO_COL(x) (7-x%8)
#define POS_TO_ROW(x) (x/8)
#define POS_TO_COL_CHAR(x) (POS_TO_COL(x)+'a')
#define POS_TO_ROW_CHAR(x) (POS_TO_ROW(x)+'1')
#define GUI_Send(...); printf(__VA_ARGS__); fflush(stdout);
#define HASHTABLE_SIZE_MIN        0
#define HASHTABLE_SIZE_DEFAULT  128
#define HASHTABLE_SIZE_MAX     2048
#define HISTORY_SIZE_MAX       1024
#define INF 1000000
#define MOVES_ALL      0
#define MOVES_CAPTURES 1
#define CONTEMPT_VALUE 100

#define U64_COL_H 0x0101010101010101ULL
#define U64_COL_G 0x0202020202020202ULL
#define U64_COL_F 0x0404040404040404ULL
#define U64_COL_E 0x0808080808080808ULL
#define U64_COL_D 0x1010101010101010ULL
#define U64_COL_C 0x2020202020202020ULL
#define U64_COL_B 0x4040404040404040ULL
#define U64_COL_A 0x8080808080808080ULL
#define U64_ROW_1 0x00000000000000FFULL
#define U64_ROW_2 0x000000000000FF00ULL
#define U64_ROW_3 0x0000000000FF0000ULL
#define U64_ROW_4 0x00000000FF000000ULL
#define U64_ROW_5 0x000000FF00000000ULL
#define U64_ROW_6 0x0000FF0000000000ULL
#define U64_ROW_7 0x00FF000000000000ULL
#define U64_ROW_8 0xFF00000000000000ULL

#define U64_A1 (U64_COL_A & U64_ROW_1)
#define U64_B1 (U64_COL_B & U64_ROW_1)
#define U64_C1 (U64_COL_C & U64_ROW_1)
#define U64_D1 (U64_COL_D & U64_ROW_1)
#define U64_E1 (U64_COL_E & U64_ROW_1)
#define U64_F1 (U64_COL_F & U64_ROW_1)
#define U64_G1 (U64_COL_G & U64_ROW_1)
#define U64_H1 (U64_COL_H & U64_ROW_1)

#define U64_A4 (U64_COL_A & U64_ROW_4)
#define U64_B4 (U64_COL_B & U64_ROW_4)
#define U64_C4 (U64_COL_C & U64_ROW_4)
#define U64_D4 (U64_COL_D & U64_ROW_4)
#define U64_E4 (U64_COL_E & U64_ROW_4)
#define U64_F4 (U64_COL_F & U64_ROW_4)
#define U64_G4 (U64_COL_G & U64_ROW_4)
#define U64_H4 (U64_COL_H & U64_ROW_4)

#define U64_A5 (U64_COL_A & U64_ROW_5)
#define U64_B5 (U64_COL_B & U64_ROW_5)
#define U64_C5 (U64_COL_C & U64_ROW_5)
#define U64_D5 (U64_COL_D & U64_ROW_5)
#define U64_E5 (U64_COL_E & U64_ROW_5)
#define U64_F5 (U64_COL_F & U64_ROW_5)
#define U64_G5 (U64_COL_G & U64_ROW_5)
#define U64_H5 (U64_COL_H & U64_ROW_5)

#define U64_A8 (U64_COL_A & U64_ROW_8)
#define U64_B8 (U64_COL_B & U64_ROW_8)
#define U64_C8 (U64_COL_C & U64_ROW_8)
#define U64_D8 (U64_COL_D & U64_ROW_8)
#define U64_E8 (U64_COL_E & U64_ROW_8)
#define U64_F8 (U64_COL_F & U64_ROW_8)
#define U64_G8 (U64_COL_G & U64_ROW_8)
#define U64_H8 (U64_COL_H & U64_ROW_8)

#define QUIESCENCE_SEARCH
#define HASHTABLE
#define NULL_MOVE

enum {WHITE, BLACK, BOTH};
enum {wP, bP, KNIGHTS, BISHOPS, ROOKS, QUEENS, KINGS, EMPTY};
enum {wKSC, bKSC, wQSC, bQSC};
enum {KSC, QSC, QUIET, DOUBLE_PAWN, CAPTURE, PROMOTE, EP};
enum {EXACT, LOWERBOUND, UPPERBOUND};

enum {H8=56, G8, F8, E8, D8, C8, B8, A8};
enum {H7=48, G7, F7, E7, D7, C7, B7, A7};
enum {H6=40, G6, F6, E6, D6, C6, B6, A6};
enum {H5=32, G5, F5, E5, D5, C5, B5, A5};
enum {H4=24, G4, F4, E4, D4, C4, B4, A4};
enum {H3=16, G3, F3, E3, D3, C3, B3, A3};
enum {H2= 8, G2, F2, E2, D2, C2, B2, A2};
enum {H1= 0, G1, F1, E1, D1, C1, B1, A1};

typedef struct
{
  uint8_t from;
  uint8_t to;
  uint8_t taken;
  uint8_t piece_type;
  uint8_t type;
  uint8_t promotion;
  
  #ifdef HASHTABLE
    uint64_t key_old;
  #endif
  uint64_t ep_old;
  uint8_t num_halfmoves_old;
  uint8_t castling[4];
} s_move;

typedef struct
{
  int num_moves;
  s_move moves[MAX_DEPTH];
} s_pv;

typedef struct
{
  int turn;
  uint8_t castling[4];
  uint64_t ep;
  uint64_t combined[7];
  uint64_t colour[2];
  #ifdef HASHTABLE
    uint64_t key;
  #endif
  uint8_t num_halfmoves;
  int history_size;
  uint64_t key_history[HISTORY_SIZE_MAX];
} s_board;

typedef struct
{
  uint8_t flags;
  uint64_t key;
  uint8_t depth;
  int eval;
  s_move pv;
} s_hashtable_entry;

typedef struct
{
  s_hashtable_entry *entries;
  int num_entries;
  int max_entries;
  int size_bytes;
} s_hashtable;

typedef struct
{
  int wtime;
  int btime;
  int winc;
  int binc;
  int movestogo;
  int depth;
  int nodes;
  int mate;
  int movetime;
  clock_t time_max;
} s_search_info;

typedef struct
{
  s_board *board;
  s_search_info *info;
} s_thread_data;

typedef struct
{
  int out_of_time;
  int time_taken;
  uint64_t nodes;
  int best_move_num;
  
  int num_moves;
  s_move moves[MAX_MOVES];
  int evals[MAX_MOVES];
  s_pv pvs[MAX_MOVES];
} s_search_results;

s_hashtable *hashtable;
uint64_t key_piece_positions[7][2][10*12];
uint64_t key_turn;
uint64_t key_castling[4];
uint64_t key_ep_col[8];
uint64_t key_ksc[2];
uint64_t key_qsc[2];

uint64_t ksc_king[2];
uint64_t ksc_rook[2];
uint64_t qsc_king[2];
uint64_t qsc_rook[2];

// attack.c
int square_attacked(s_board* board, uint64_t pos, int side);

// bitboards.c
void bitboards_init();
uint64_t magic_moves_hor_ver(uint64_t pieces_all, int pos);
uint64_t magic_moves_diagonal(uint64_t pieces_all, int pos);
uint64_t magic_moves_knight(int pos);
uint64_t magic_moves_king(int pos);
int u64_to_sq(uint64_t pos);
int u64_col(uint64_t pos);
int u64_row(uint64_t pos);
uint64_t pinned_pieces_white(s_board* board, int sq);
uint64_t pinned_pieces_black(s_board* board, int sq);
int error_check(s_board* board);

// search.c
int search_info_set(s_search_info info);
void *search_base(void *n);
s_search_results search(s_board* board, int depth);
int alpha_beta(s_board* board, int alpha, int beta, int depth, int null_allowed, s_pv *pv);

// hash_table.c
void key_init();
uint64_t create_key_board(s_board *board);
int hashtable_init(s_hashtable *hashtable, int size_megabytes);
void hashtable_clear(s_hashtable *hashtable);
void hashtable_free(s_hashtable *hashtable);
s_hashtable_entry *hashtable_poll(s_hashtable *hashtable, uint64_t key);
s_hashtable_entry *hashtable_add(s_hashtable *hashtable, int flags, uint64_t key, int depth, int eval, s_move pv);

// eval.c
int is_endgame(s_board* board);
int is_fifty_move_draw(s_board* board);
int is_threefold(s_board* board);
int eval(s_board* board);

// movegen.c
int find_moves(s_board* board, s_move* move_list, int colour);
int find_moves_captures(s_board* board, s_move* move_list, int colour);
int find_moves_quiet(s_board* board, s_move* move_list, int colour);
int find_moves_wP_quiet(s_board* board, s_move* move_list);
int find_moves_wP_captures(s_board* board, s_move* move_list);
int find_moves_bP_quiet(s_board* board, s_move* move_list);
int find_moves_bP_captures(s_board* board, s_move* move_list);
int find_moves_knights(s_board* board, s_move* move_list, uint64_t allowed);
int find_moves_bishops_queens(s_board* board, s_move* move_list, uint64_t allowed);
int find_moves_rooks_queens(s_board* board, s_move* move_list, uint64_t allowed);
int find_moves_kings_quiet(s_board* board, s_move* move_list);
int find_moves_kings_captures(s_board* board, s_move* move_list);

// fen.c
int set_fen(s_board *board, const char *fen);

// perft.c
void perft(s_board* board, int max_depth, char* fen);
int perft_split(s_board* board, int depth, char* fen);
void perft_suite(s_board* board, int max_depth, char* filepath);
void perft_suite_search(s_board* board, int max_depth, char* filepath);
int perft_movegen(s_board* board, const char* filepath);
int perft_movegen_sides(s_board* board, const char* filepath);

// move.c
s_move move_add(s_board *board, int from, int to, int type, int piece_type);
int move_add_pawn_white(s_board* board, s_move* move_list, int from, int to);
int move_add_pawn_black(s_board* board, s_move* move_list, int from, int to);
s_move add_movecapture(s_board* board, int from, int to, int piece_type);
s_move add_promotion_move(s_board *board, int from, int to, int piece_type, int promo_piece);
void move_make(s_board *board, s_move *move);
void move_undo(s_board *board, s_move *move);
int moves_sort(s_move* moves, int num);
void move_make_ascii(s_board *board, char *move_string);
int move_to_string(char* string, s_move *move);
int move_is_legal(s_board* board, s_move* move);

// display.c
void print_move(s_move move);
void print_moves(s_move* moves, int num_moves);
void print_u64(uint64_t board);
void display_board(s_board *board);
void display_history(s_board* board);

// uci.c
void uci_listen();

#endif // DEFS_H_INCLUDED