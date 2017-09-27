    return APR_ENOMEM;
}

/*
 * print purge statistics
 */
static void printstats(apr_off_t total, apr_off_t sum, apr_off_t max,
                       apr_off_t etotal, apr_off_t entries)
{
    char ttype, stype, mtype, utype;
    apr_off_t tfrag, sfrag, ufrag;

    if (!verbose) {
        return;
    }

    ttype = 'K';
    tfrag = ((total * 10) / KBYTE) % 10;
    total /= KBYTE;
    if (total >= KBYTE) {
        ttype = 'M';
        tfrag = ((total * 10) / KBYTE) % 10;
        total /= KBYTE;
    }

    stype = 'K';
    sfrag = ((sum * 10) / KBYTE) % 10;
    sum /= KBYTE;
    if (sum >= KBYTE) {
        stype = 'M';
        sfrag = ((sum * 10) / KBYTE) % 10;
        sum /= KBYTE;
    }

    mtype = 'K';
    max /= KBYTE;
    if (max >= KBYTE) {
        mtype = 'M';
        max /= KBYTE;
    }

    apr_file_printf(errfile, "Statistics:" APR_EOL_STR);
    if (unsolicited) {
        utype = 'K';
        ufrag = ((unsolicited * 10) / KBYTE) % 10;
        unsolicited /= KBYTE;
        if (unsolicited >= KBYTE) {
            utype = 'M';
