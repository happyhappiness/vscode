uint32_t
get4byt(void)
{
    uint32_t var;

    var=(uint32_t)((p[bpos]<<0) | (p[bpos+1]<<8) | (p[bpos+2]<<16) | (p[bpos+3]<<24));
    bpos = bpos+4;

    return var;
}