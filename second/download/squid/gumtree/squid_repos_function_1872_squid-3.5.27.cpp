static int
saneDiff(time_t diff)
{
    return abs((int) diff) > squid_curtime / 2 ? 0 : diff;
}