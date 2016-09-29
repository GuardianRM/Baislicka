#include "defs.h"
#include <string.h>

int moves_sort(s_move* moves, int num)
{
  assert(moves != NULL);
  assert(num >= 0);
  assert(num <= MAX_MOVES);
  
  s_move store;
  
  int pos = 0;
  
  int i;
  
  // Put all captures first
  for(i = 0; i < num; ++i)
  {
    if(moves[i].type == CAPTURE)
    {
      store = moves[pos];
      moves[pos] = moves[i];
      moves[i] = store;
      
      pos++;
    }
  }
  
  // Put all queen captures first
  int pos_queen = 0;
  for(i = 0; i < pos; ++i)
  {
    if(moves[i].taken == wQ || moves[i].taken == bQ)
    {
      store = moves[pos_queen];
      moves[pos_queen] = moves[i];
      moves[i] = store;
      
      pos_queen++;
    }
  }
  
  int capturing_piece = 0;
  
  // Put all pawns capturing first
  for(i = 0; i < pos_queen; ++i)
  {
    if(moves[i].piece_type == wP || moves[i].piece_type == bP)
    {
      store = moves[capturing_piece];
      moves[capturing_piece] = moves[i];
      moves[i] = store;
      
      capturing_piece++;
    }
  }
  
  // Put all knights & bishops next
  for(i = capturing_piece; i < pos_queen; ++i)
  {
    if(moves[i].piece_type == wN || moves[i].piece_type == bN || moves[i].piece_type == wB || moves[i].piece_type == bB)
    {
      store = moves[capturing_piece];
      moves[capturing_piece] = moves[i];
      moves[i] = store;
        
      capturing_piece++;
    }
  }
  
  // Put all rook captures second
  int pos_rook = pos_queen;
  for(i = pos_queen; i < pos; ++i)
  {
    if(moves[i].taken == wR || moves[i].taken == bR)
    {
      store = moves[pos_rook];
      moves[pos_rook] = moves[i];
      moves[i] = store;
      
      pos_rook++;
    }
  }
  
  capturing_piece = pos_queen;
    
  // Put all pawns capturing first
  for(i = pos_queen; i < pos_rook; ++i)
  {
    if(moves[i].piece_type == wP || moves[i].piece_type == bP)
    {
      store = moves[capturing_piece];
      moves[capturing_piece] = moves[i];
      moves[i] = store;
        
      capturing_piece++;
    }
  }
  
  // Put all knights & bishops next
  for(i = capturing_piece; i < pos_rook; ++i)
  {
    if(moves[i].piece_type == wN || moves[i].piece_type == bN || moves[i].piece_type == wB || moves[i].piece_type == bB)
    {
      store = moves[capturing_piece];
      moves[capturing_piece] = moves[i];
      moves[i] = store;
        
      capturing_piece++;
    }
  }
  
  /*
  // Put all bishops & knights captures third
  int pos_bn = 0;
  for(i = pos_rook; i < pos; ++i)
  {
    if(moves[i].taken == wB || moves[i].taken == bB || moves[i].taken == wN || moves[i].taken == bN)
    {
      store = moves[pos_bn];
      moves[pos_bn] = moves[i];
      moves[i] = store;
      
      pos_bn++;
    }
  }
  */
  
  return 0;
}

int move_add_pawn_white(s_board* board, s_move* moves, uint64_t from, uint64_t to)
{
  assert(board != NULL);
  assert(moves != NULL);
  
  if(to&U64_ROW_8)
  {
    moves[0] = add_promotion_move(board, from, to, wP, wQ);
    moves[1] = add_promotion_move(board, from, to, wP, wN);
    moves[2] = add_promotion_move(board, from, to, wP, wR);
    moves[3] = add_promotion_move(board, from, to, wP, wB);
    return 4;
  }
  else
  {
    moves[0] = add_movecapture_white(board, from, to, wP);
    return 1;
  }
}

int move_add_pawn_black(s_board* board, s_move* moves, uint64_t from, uint64_t to)
{
  assert(board != NULL);
  assert(moves != NULL);
  
  if(to&U64_ROW_1)
  {
    moves[0] = add_promotion_move(board, from, to, bP, bQ);
    moves[1] = add_promotion_move(board, from, to, bP, bN);
    moves[2] = add_promotion_move(board, from, to, bP, bR);
    moves[3] = add_promotion_move(board, from, to, bP, bB);
    return 4;
  }
  else
  {
    moves[0] = add_movecapture_black(board, from, to, bP);
    return 1;
  }
}

s_move add_promotion_move(s_board *board, uint64_t from, uint64_t to, int piece_type, int promo_piece)
{
  assert(board != NULL);
  assert(from);
  assert(to);
  
  s_move move;
  
  move.taken = EMPTY;
  int n;
  for(n = 0; n < 12; ++n)
  {
    if(board->pieces[n]&to)
    {
      move.taken = n;
      break;
    }
  }
  
  move.from = from;
  move.to = to;
  move.type = PROMOTE;
  move.piece_type = piece_type;
  move.promotion = promo_piece;
  return move;
}

s_move add_movecapture_white(s_board* board, uint64_t from, uint64_t to, int piece_type)
{
  assert(board != NULL);
  assert(from);
  assert(to);
  assert(piece_type == wP || piece_type == wN || piece_type == wB || piece_type == wR || piece_type == wQ || piece_type == wK);
  
  if(board->pieces_colour[BLACK]&to)
  {
    return move_add(board, from, to, CAPTURE, piece_type);
  }
  else
  {
    return move_add(board, from, to, QUIET, piece_type);
  }
}

s_move add_movecapture_black(s_board* board, uint64_t from, uint64_t to, int piece_type)
{
  assert(board != NULL);
  assert(from);
  assert(to);
  assert(piece_type == bP || piece_type == bN || piece_type == bB || piece_type == bR || piece_type == bQ || piece_type == bK);
  
  if(board->pieces_colour[WHITE]&to)
  {
    return move_add(board, from, to, CAPTURE, piece_type);
  }
  else
  {
    return move_add(board, from, to, QUIET, piece_type);
  }
}

s_move move_add(s_board *board, uint64_t from, uint64_t to, int type, int piece_type)
{
  assert(board != NULL);
  assert(from);
  assert(to);
  
  int taken = EMPTY;
  if(type == CAPTURE)
  {
    int n;
    for(n = 0; n < 12; ++n)
    {
      if(board->pieces[n]&to) {taken = n; break;}
    }
  }
  else if(type == EP)
  {
    if(piece_type == wP)
    {
      taken = bP;
    }
    else
    {
      taken = wP;
    }
  }
  
  s_move move;
  move.from = from;
  move.to = to;
  move.type = type;
  move.taken = taken;
  move.piece_type = piece_type;
  return move;
}

void move_make(s_board *board, s_move *move)
{
  assert(board != NULL);
  assert(move != NULL);
  
  // set old permissions
  #ifdef HASHTABLE
    move->key_old = board->key;
  #endif
  move->ep_old = board->ep;
  move->castling[wKSC] = board->castling[wKSC];
  move->castling[wQSC] = board->castling[wQSC];
  move->castling[bKSC] = board->castling[bKSC];
  move->castling[bQSC] = board->castling[bQSC];
  
  #ifdef HASHTABLE
    if(board->ep)
    {
      board->key ^= key_ep_col[u64_col(board->ep)];
    }
  #endif
  
  board->ep = 0;
  
  // White king move
  if((move->from) & U64_E1)
  {
    board->castling[wQSC] = 0;
    board->castling[wKSC] = 0;
  }
  // A1 move
  else if((move->to&U64_A1) || (move->from&U64_A1))
  {
    board->castling[wQSC] = 0;
  }
  // H1 move
  else if((move->to&U64_H1) || (move->from&U64_H1))
  {
    board->castling[wKSC] = 0;
  }
  
  // Black king move
  if(move->from & U64_E8)
  {
    board->castling[bQSC] = 0;
    board->castling[bKSC] = 0;
  }
  // A8 move
  else if((move->to&U64_A8) || (move->from&U64_A8))
  {
    board->castling[bQSC] = 0;
  }
  // H8 move
  else if((move->to&U64_H8) || (move->from&U64_H8))
  {
    board->castling[bKSC] = 0;
  }
  
  #ifdef HASHTABLE
    int sq_from = u64_to_sq(move->from);
    int sq_to = u64_to_sq(move->to);
  #endif
  
  switch(move->type)
  {
    case QUIET:
      board->pieces[move->piece_type] ^= move->from;
      board->pieces[move->piece_type] ^= move->to;
      
      #ifdef HASHTABLE
        board->key ^= key_piece_positions[move->piece_type][sq_from];
        board->key ^= key_piece_positions[move->piece_type][sq_to];
      #endif
      break;
    case CAPTURE:
      board->pieces[move->piece_type] ^= move->from;
      board->pieces[move->piece_type] ^= move->to;
      board->pieces[move->taken] ^= move->to;
      
      #ifdef HASHTABLE
        board->key ^= key_piece_positions[move->piece_type][sq_from];
        board->key ^= key_piece_positions[move->piece_type][sq_to];
        board->key ^= key_piece_positions[move->taken][sq_to];
      #endif
      break;
    case DOUBLE_PAWN:
      board->pieces[move->piece_type] ^= move->from;
      board->pieces[move->piece_type] ^= move->to;
      // Add ep square
      if(move->piece_type == wP)
      {
        board->ep = (move->to)>>8;
      }
      else
      {
        board->ep = (move->to)<<8;
      }
      
      #ifdef HASHTABLE
        board->key ^= key_piece_positions[move->piece_type][sq_from];
        board->key ^= key_piece_positions[move->piece_type][sq_to];
        board->key ^= key_ep_col[u64_col(board->ep)];
      #endif
      break;
    case PROMOTE:
      board->pieces[move->piece_type] ^= move->from;
      board->pieces[move->promotion] ^= move->to;
      if(move->taken != EMPTY)
      {
        board->pieces[move->taken] ^= move->to;
      }
      
      #ifdef HASHTABLE
        board->key ^= key_piece_positions[move->piece_type][sq_from];
        board->key ^= key_piece_positions[move->promotion][sq_to];
        if(move->taken != EMPTY)
        {
          board->key ^= key_piece_positions[move->taken][sq_to];
        }
      #endif
      break;
    case EP:
      board->pieces[move->piece_type] ^= move->from;
      board->pieces[move->piece_type] ^= move->to;
      if(move->piece_type == wP)
      {
        board->pieces[bP] ^= (move->to)>>8;
      }
      else
      {
        board->pieces[wP] ^= (move->to)<<8;
      }
      
      #ifdef HASHTABLE
        board->key ^= key_piece_positions[move->piece_type][sq_from];
        board->key ^= key_piece_positions[move->piece_type][sq_to];
        if(move->piece_type == wP)
        {
          board->key ^= key_piece_positions[bP][sq_to-8];
        }
        else
        {
          board->key ^= key_piece_positions[wP][sq_to+8];
        }
      #endif
      break;
    case wKSC:
      board->pieces[wK] ^= U64_E1;
      board->pieces[wK] ^= U64_G1;
      board->pieces[wR] ^= U64_H1;
      board->pieces[wR] ^= U64_F1;
      
      #ifdef HASHTABLE
        board->key ^= key_piece_positions[wK][E1];
        board->key ^= key_piece_positions[wK][G1];
        board->key ^= key_piece_positions[wR][H1];
        board->key ^= key_piece_positions[wR][F1];
      #endif
      break;
    case wQSC:
      board->pieces[wK] ^= U64_E1;
      board->pieces[wK] ^= U64_C1;
      board->pieces[wR] ^= U64_A1;
      board->pieces[wR] ^= U64_D1;
      
      #ifdef HASHTABLE
        board->key ^= key_piece_positions[wK][E1];
        board->key ^= key_piece_positions[wK][C1];
        board->key ^= key_piece_positions[wR][A1];
        board->key ^= key_piece_positions[wR][D1];
      #endif
      break;
    case bKSC:
      board->pieces[bK] ^= U64_E8;
      board->pieces[bK] ^= U64_G8;
      board->pieces[bR] ^= U64_H8;
      board->pieces[bR] ^= U64_F8;
      
      #ifdef HASHTABLE
        board->key ^= key_piece_positions[bK][E8];
        board->key ^= key_piece_positions[bK][G8];
        board->key ^= key_piece_positions[bK][H8];
        board->key ^= key_piece_positions[bK][F8];
      #endif
      break;
    case bQSC:
      board->pieces[bK] ^= U64_E8;
      board->pieces[bK] ^= U64_C8;
      board->pieces[bR] ^= U64_A8;
      board->pieces[bR] ^= U64_D8;
      
      #ifdef HASHTABLE
        board->key ^= key_piece_positions[bK][E8];
        board->key ^= key_piece_positions[bK][C8];
        board->key ^= key_piece_positions[bK][A8];
        board->key ^= key_piece_positions[bK][D8];
      #endif
      break;
  }
  
  #ifdef HASHTABLE
    if(board->castling[wKSC] != move->castling[wKSC]) {board->key ^= key_castling[wKSC];}
    if(board->castling[wQSC] != move->castling[wQSC]) {board->key ^= key_castling[wQSC];}
    if(board->castling[bKSC] != move->castling[bKSC]) {board->key ^= key_castling[bKSC];}
    if(board->castling[bQSC] != move->castling[bQSC]) {board->key ^= key_castling[bQSC];}
    board->key ^= key_turn;
  #endif
  
  board->pieces_colour[WHITE] = board->pieces[wP] | board->pieces[wN] | board->pieces[wB] |
                                board->pieces[wR] | board->pieces[wQ] | board->pieces[wK];
  
  board->pieces_colour[BLACK] = board->pieces[bP] | board->pieces[bN] | board->pieces[bB] |
                                board->pieces[bR] | board->pieces[bQ] | board->pieces[bK];
  
  board->pieces_all = board->pieces_colour[WHITE] | board->pieces_colour[BLACK];
}

void move_undo(s_board *board, s_move *move)
{  
  switch(move->type)
  {
    case QUIET:
      board->pieces[move->piece_type] ^= move->from;
      board->pieces[move->piece_type] ^= move->to;
      break;
    case CAPTURE:
      board->pieces[move->piece_type] ^= move->from;
      board->pieces[move->piece_type] ^= move->to;
      board->pieces[move->taken] ^= move->to;
      break;
    case DOUBLE_PAWN:
      board->pieces[move->piece_type] ^= move->from;
      board->pieces[move->piece_type] ^= move->to;
      break;
    case PROMOTE:
      board->pieces[move->piece_type] ^= move->from;
      board->pieces[move->promotion] ^= move->to;
      if(move->taken != EMPTY)
      {
        board->pieces[move->taken] ^= move->to;
      }
      break;
    case EP:
      board->pieces[move->piece_type] ^= move->from;
      board->pieces[move->piece_type] ^= move->to;
      if(move->piece_type == wP)
      {
        board->pieces[bP] ^= (move->to)>>8;
      }
      else
      {
        board->pieces[wP] ^= (move->to)<<8;
      }
      break;
    case wKSC:
      board->pieces[wK] ^= U64_E1;
      board->pieces[wK] ^= U64_G1;
      board->pieces[wR] ^= U64_H1;
      board->pieces[wR] ^= U64_F1;
      break;
    case wQSC:
      board->pieces[wK] ^= U64_E1;
      board->pieces[wK] ^= U64_C1;
      board->pieces[wR] ^= U64_A1;
      board->pieces[wR] ^= U64_D1;
      break;
    case bKSC:
      board->pieces[bK] ^= U64_E8;
      board->pieces[bK] ^= U64_G8;
      board->pieces[bR] ^= U64_H8;
      board->pieces[bR] ^= U64_F8;
      break;
    case bQSC:
      board->pieces[bK] ^= U64_E8;
      board->pieces[bK] ^= U64_C8;
      board->pieces[bR] ^= U64_A8;
      board->pieces[bR] ^= U64_D8;
      break;
  }
  
  #ifdef HASHTABLE
    board->key = move->key_old;
  #endif
  board->ep = move->ep_old;
  board->castling[wKSC] = move->castling[wKSC];
  board->castling[wQSC] = move->castling[wQSC];
  board->castling[bKSC] = move->castling[bKSC];
  board->castling[bQSC] = move->castling[bQSC];
  
  board->pieces_colour[WHITE] = board->pieces[wP] | board->pieces[wN] | board->pieces[wB] |
                                board->pieces[wR] | board->pieces[wQ] | board->pieces[wK];
  
  board->pieces_colour[BLACK] = board->pieces[bP] | board->pieces[bN] | board->pieces[bB] |
                                board->pieces[bR] | board->pieces[bQ] | board->pieces[bK];
  
  board->pieces_all = board->pieces_colour[WHITE] | board->pieces_colour[BLACK];
}

void move_make_ascii(s_board *board, char *move_string)
{
  assert(board != NULL);
  assert(move_string != NULL);

  int from_col = move_string[0] - 'a';
  int from_row = move_string[1] - '1';
  int to_col = move_string[2] - 'a';
  int to_row = move_string[3] - '1';
  
  assert(from_col >= 0);
  assert(from_col < 8);
  assert(from_row >= 0);
  assert(from_row < 8);
  assert(to_col >= 0);
  assert(to_col < 8);
  assert(to_row >= 0);
  assert(to_row < 8);
  
  uint64_t from = ((uint64_t)1<<(7-from_col))<<(8*from_row);
  uint64_t to = ((uint64_t)1<<(7-to_col))<<(8*to_row);
  
  int piece_type = -1;
  int piece_taken = -1;
  int move_type = QUIET;
  int promo_piece = -1;
  
  int i;
  for(i = 0; i < 12; ++i)
  {
    if(board->pieces[i]&from)
    {
      piece_type = i;
    }
    if(board->pieces[i]&to)
    {
      piece_taken = i;
    }
  }
  
  if(piece_taken != -1)
  {
    move_type = CAPTURE;
  }
  
  assert(piece_type >= 0);
  assert(piece_type < 12);
  
  if(strlen(move_string) > 4)
  {
    if(move_string[4] == 'Q' || move_string[4] == 'q')
    {
           if(piece_type == wP) {promo_piece = wQ;}
      else if(piece_type == bP) {promo_piece = bQ;}
    }
    else if(move_string[4] == 'R' || move_string[4] == 'r')
    {
           if(piece_type == wP) {promo_piece = wR;}
      else if(piece_type == bP) {promo_piece = bR;}
    }
    else if(move_string[4] == 'B' || move_string[4] == 'b')
    {
           if(piece_type == wP) {promo_piece = wB;}
      else if(piece_type == bP) {promo_piece = bB;}
    }
    else if(move_string[4] == 'N' || move_string[4] == 'n')
    {
           if(piece_type == wP) {promo_piece = wN;}
      else if(piece_type == bP) {promo_piece = bN;}
    }
  }
  
  if(piece_type == wK)
  {
    if(from == U64_E1 && to == U64_G1)
    {
      move_type = wKSC;
    }
    else if(from == U64_E1 && to == U64_C1)
    {
      move_type = wQSC;
    }
  }
  else if(piece_type == bK)
  {
    if(from == U64_E8 && to == U64_G8)
    {
      move_type = bKSC;
    }
    else if(from == U64_E8 && to == U64_C8)
    {
      move_type = bQSC;
    }
  }
  
  if(piece_type == wP)
  {
    if(from_col != to_col)
    {
      // en passant
      if(piece_taken == -1)
      {
        piece_taken = bP;
        move_type = EP;
      }
      else
      {
        move_type = CAPTURE;
      }
    }
    else if(to_row - from_row == 2)
    {
      move_type = DOUBLE_PAWN;
    }
  }
  else if(piece_type == bP)
  {
    if(from_col != to_col)
    {
      // en passant
      if(piece_taken == -1)
      {
        piece_taken = wP;
        move_type = EP;
      }
      else
      {
        move_type = CAPTURE;
      }
    }
    else if(to_row - from_row == -2)
    {
      move_type = DOUBLE_PAWN;
    }
  }
  
  if(promo_piece != -1)
  {
    move_type = PROMOTE;
  }
  
  s_move move;
  move.from = from;
  move.to = to;
  move.type = move_type;
  move.taken = piece_taken;
  move.piece_type = piece_type;
  move.promotion = promo_piece;

  move_make(board, &move);
}

int move_to_string(char* string, s_move *move)
{
  assert(string != NULL);
  assert(move != NULL);
  
  string[0] = 'a' + u64_col(move->from);
  string[1] = '1' + u64_row(move->from);
  string[2] = 'a' + u64_col(move->to);
  string[3] = '1' + u64_row(move->to);
  string[4] = '\0';
  
  if(move->type == PROMOTE)
  {
    if(move->promotion == wQ || move->promotion == bQ) {string[4] = 'Q';}
    if(move->promotion == wR || move->promotion == bR) {string[4] = 'R';}
    if(move->promotion == wB || move->promotion == bB) {string[4] = 'B';}
    if(move->promotion == wN || move->promotion == bN) {string[4] = 'N';}
    string[5] = '\0';
  }
  
  return 0;
}

int move_is_legal(s_board* board, s_move* move)
{
  assert(board != NULL);
  assert(move != NULL);
  
  if((board->pieces[move->piece_type] & move->from) == 0) {return -1;}
  
  s_move move_list[MAX_MOVES];
  
  int num_moves = 0;
  switch(move->piece_type)
  {
    case wP:
      num_moves = find_moves_wP(board, move_list);
      break;
    case wN:
      num_moves = find_moves_wN(board, move_list);
      break;
    case wB:
      num_moves = find_moves_wB(board, move_list);
      break;
    case wR:
      num_moves = find_moves_wR(board, move_list);
      break;
    case wQ:
      num_moves = find_moves_wQ(board, move_list);
      break;
    case wK:
      num_moves = find_moves_wK(board, move_list);
      break;
    case bP:
      num_moves = find_moves_bP(board, move_list);
      break;
    case bN:
      num_moves = find_moves_bN(board, move_list);
      break;
    case bB:
      num_moves = find_moves_bB(board, move_list);
      break;
    case bR:
      num_moves = find_moves_bR(board, move_list);
      break;
    case bQ:
      num_moves = find_moves_bQ(board, move_list);
      break;
    case bK:
      num_moves = find_moves_bK(board, move_list);
      break;
  }
  
  int i;
  for(i = 0; i < num_moves; ++i)
  {
    if(move_list[i].from == move->from &&
       move_list[i].to == move->to &&
       move_list[i].type == move->type)
    {
      return 0;
    }
  }
  
  return -1;
  
  /*
  switch(move->type)
  {
    case QUIET:
      if((board->pieces[move->piece_type] & move->from) == 0)
        return -1;
      if((board->pieces_all & move->to) == 0)
        return -1;
      break;
    case DOUBLE_PAWN:
      break;
    case CAPTURE:
      break;
    case PROMOTE:
      break;
    case EP:
      break;
    case wKSC:
      if(!board->castling[wKSC])
        return -1;
      if(board->pieces_all&U64_F1)
        return -1;
      if(board->pieces_all&U64_G1)
        return -1;
      break;
    case wQSC:
      if(!board->castling[wQSC])
        return -1;
      if(board->pieces_all&U64_D1)
        return -1;
      if(board->pieces_all&U64_C1)
        return -1;
      if(board->pieces_all&U64_B1)
        return -1;
      break;
    case bKSC:
      if(!board->castling[bKSC])
        return -1;
      if(board->pieces_all&U64_F8)
        return -1;
      if(board->pieces_all&U64_G8)
        return -1;
      break;
    case bQSC:
      if(!board->castling[bQSC])
        return -1;
      if(board->pieces_all&U64_D8)
        return -1;
      if(board->pieces_all&U64_C8)
        return -1;
      if(board->pieces_all&U64_B8)
        return -1;
      break;
  }
  */
}
