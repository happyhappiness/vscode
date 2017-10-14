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
            ufrag = ((unsolicited * 10) / KBYTE) % 10;
            unsolicited /= KBYTE;
        }
        if (!unsolicited && !ufrag) {
            ufrag = 1;
        }
        apr_file_printf(errfile, "unsolicited size %d.%d%c" APR_EOL_STR,
                        (int)(unsolicited), (int)(ufrag), utype);
     }
     apr_file_printf(errfile, "size limit %d.0%c" APR_EOL_STR,
                     (int)(max), mtype);
     apr_file_printf(errfile, "total size was %d.%d%c, total size now "
                              "%d.%d%c" APR_EOL_STR,
                     (int)(total), (int)(tfrag), ttype, (int)(sum),
                     (int)(sfrag), stype);
     apr_file_printf(errfile, "total entries was %d, total entries now %d"
                              APR_EOL_STR, (int)(etotal), (int)(entries));
}