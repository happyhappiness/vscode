
    abInit(&ab);
    /* Cursor to left edge */
    snprintf(seq,64,"\x1b[0G");
    abAppend(&ab,seq,strlen(seq));
    /* Write the prompt and the current buffer content */
    abAppend(&ab,l->prompt,strlen(l->prompt));
