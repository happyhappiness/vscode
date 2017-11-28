void store_op1(re_opcode_t op, unsigned char *loc, int arg)
{
    *loc = (unsigned char) op;
    STORE_NUMBER(loc + 1, arg);
}