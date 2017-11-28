static uint32
lshift(uint32 x, int s)
{
    x &= 0xFFFFFFFF;
    return ((x << s) & 0xFFFFFFFF) | (x >> (32 - s));
}