void
static byteSwap(uint32_t * buf, unsigned words)
{
    uint8_t *p = (uint8_t *) buf;

    do {
        *buf++ = (uint32_t) ((unsigned) p[3] << 8 | p[2]) << 16 |
                 ((unsigned) p[1] << 8 | p[0]);
        p += 4;
    } while (--words);
}