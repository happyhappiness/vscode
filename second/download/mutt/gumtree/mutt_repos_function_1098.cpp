static void
store_op2 (op, loc, arg1, arg2)
    re_opcode_t op;
    unsigned char *loc;
    int arg1, arg2;
{
  *loc = (unsigned char) op;
  STORE_NUMBER (loc + 1, arg1);
  STORE_NUMBER (loc + 3, arg2);
}