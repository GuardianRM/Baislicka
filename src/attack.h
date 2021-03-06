#ifndef ATTACK_H_INCLUDED
#define ATTACK_H_INCLUDED

#include "board.h"

int square_attacked(s_board *board, uint64_t pos, int side);
int get_smallest_attacker(s_board *board, int sq, int side);
int eval_attackers(s_board *board, uint64_t pos, int side);
int count_attackers(s_board *board, uint64_t pos, int side);

#endif
