uint64_t
get6byt_be(void)
{
    uint64_t var;

    var = ((uint64_t)p[bpos+5]<<0) | ((uint64_t)p[bpos+4]<<8) | ((uint64_t)p[bpos+3]<<16) | ((uint64_t)p[bpos+2]<<24) | ((uint64_t)p[bpos+1]<<32) | ((uint64_t)p[bpos]<<40);
    bpos = bpos+6;

    return var;
}