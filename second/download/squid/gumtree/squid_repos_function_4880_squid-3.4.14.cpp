bool
CossSwapDir::optionBlockSizeParse(const char *option, const char *value, int reconfiguring)
{
    assert(option);

    if (strcmp(option, "block-size") != 0)
        return false;

    if (!value)
        self_destruct();

    int blksz = atoi(value);

    if (blksz == (1 << blksz_bits))
        /* no change */
        return true;

    if (reconfiguring) {
        debugs(47, DBG_CRITICAL, "WARNING: cannot change COSS block-size while Squid is running");
        return false;
    }

    int nbits = 0;
    int check = blksz;

    while (check > 1) {
        ++nbits;
        check >>= 1;
    }

    check = 1 << nbits;

    if (check != blksz)
        fatal("COSS block-size must be a power of 2\n");

    if (nbits > 13)
        fatal("COSS block-size must be 8192 or smaller\n");

    blksz_bits = nbits;

    blksz_mask = (1 << blksz_bits) - 1;

    return true;
}