static char *terminate_description(autoindex_config_rec *d, char *desc,
                                   apr_int32_t autoindex_opts, int desc_width)
{
    int maxsize = desc_width;
    register int x;

    /* 
     * If there's no DescriptionWidth in effect, default to the old
     * behaviour of adjusting the description size depending upon 
     * what else is being displayed.  Otherwise, stick with the 
     * setting. 
     */ 
    if (d->desc_adjust == K_UNSET) { 
        if (autoindex_opts & SUPPRESS_ICON) {
            maxsize += 6;
        }
        if (autoindex_opts & SUPPRESS_LAST_MOD) {
            maxsize += 19;
        }
        if (autoindex_opts & SUPPRESS_SIZE) {
            maxsize += 7;
        }
    }
    for (x = 0; desc[x] && ((maxsize > 0) || (desc[x] == '<')); x++) {
        if (desc[x] == '<') {
            while (desc[x] != '>') {
                if (!desc[x]) {
                    maxsize = 0;
                    break;
                }
                ++x;
            }
        }
        else if (desc[x] == '&') {
            /* entities like &auml; count as one character */
            --maxsize;
            for ( ; desc[x] != ';'; ++x) {
                if (desc[x] == '\0') {
                     maxsize = 0;
                     break;
                }
            }
        }
        else {
            --maxsize;
        }
    }
    if (!maxsize && desc[x] != '\0') {
        desc[x - 1] = '>';      /* Grump. */
        desc[x] = '\0';         /* Double Grump! */
    }
    return desc;
}