    return APR_ENOMEM;
}

/*
 * print purge statistics
 */
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
