void
insert_op2(re_opcode_t op, unsigned char *loc, int arg1, int arg2, unsigned char *end)
{
    register unsigned char *pfrom = end;
    register unsigned char *pto = end + 5;

    while (pfrom != loc)
        *--pto = *--pfrom;

    store_op2(op, loc, arg1, arg2);
}