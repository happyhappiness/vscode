    }

    /* Set column. */
    lndebug("set col %d", 1+((plen+(int)l->pos) % (int)l->cols));
    snprintf(seq,64,"\x1b[%dG", 1+((plen+(int)l->pos) % (int)l->cols));
    abAppend(&ab,seq,strlen(seq));

    lndebug("\n");
