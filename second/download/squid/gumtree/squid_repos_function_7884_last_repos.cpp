void
insert_op1(re_opcode_t op, unsigned char *loc, int arg, unsigned char *end)
{
    register unsigned char *pfrom = end;
    register unsigned char *pto = end + 3;

    while (pfrom != loc)
        *--pto = *--pfrom;

    store_op1(op, loc, arg);
}