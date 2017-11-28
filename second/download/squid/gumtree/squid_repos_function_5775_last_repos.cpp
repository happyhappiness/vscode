uint16_t
get2byt(void)
{
    uint16_t var;

    var=(uint16_t)((p[bpos]<<0) | (p[bpos+1]<<8));
    bpos = bpos+2;

    return var;
}