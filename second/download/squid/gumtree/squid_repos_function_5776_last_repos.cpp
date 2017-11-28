uint8_t
get1byt(void)
{
    uint8_t var;

    var=(uint8_t)((p[bpos]<<0));
    bpos = bpos+1;

    return var;
}