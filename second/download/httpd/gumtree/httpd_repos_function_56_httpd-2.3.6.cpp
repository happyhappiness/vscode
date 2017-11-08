static void printstats(char *path, struct stats *s)
{
    char ttype, stype, mtype, utype;
    apr_off_t tfrag, sfrag, ufrag;

    if (!verbose) {
        return;
    }

    ttype = 'K';
    tfrag = ((s->total * 10) / KBYTE) % 10;
    s->total /= KBYTE;
    if (s->total >= KBYTE) {
        ttype = 'M';
        tfrag = ((s->total * 10) / KBYTE) % 10;
        s->total /= KBYTE;
    }

    stype = 'K';
    sfrag = ((s->sum * 10) / KBYTE) % 10;
    s->sum /= KBYTE;
    if (s->sum >= KBYTE) {
        stype = 'M';
        sfrag = ((s->sum * 10) / KBYTE) % 10;
        s->sum /= KBYTE;
    }

    mtype = 'K';
    s->max /= KBYTE;
    if (s->max >= KBYTE) {
        mtype = 'M';
        s->max /= KBYTE;
    }

    apr_file_printf(errfile, "Cleaned %s. Statistics:" APR_EOL_STR, path);
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
                     (int)(s->max), mtype);
     apr_file_printf(errfile, "total size was %d.%d%c, total size now "
                              "%d.%d%c" APR_EOL_STR,
                     (int)(s->total), (int)(tfrag), ttype,
                     (int)(s->sum), (int)(sfrag), stype);
     apr_file_printf(errfile, "total entries was %d, total entries now %d"
                              APR_EOL_STR, (int)(s->etotal),
                              (int)(s->entries));
     apr_file_printf(errfile, "%d entries deleted (%d from future, %d "
                              "expired, %d fresh)" APR_EOL_STR,
                     (int)(s->etotal - s->entries), (int)(s->dfuture),
                     (int)(s->dexpired), (int)(s->dfresh));
}