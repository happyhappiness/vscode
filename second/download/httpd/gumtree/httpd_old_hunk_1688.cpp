
    if (!c->gotheader) {
        char *s;
        int l = 4;
        int space = CBUFFSIZE - c->cbx - 1;     /* -1 to allow for 0 terminator */
        int tocopy = (space < r) ? space : r;
        memcpy(c->cbuff + c->cbx, buffer, space);
        c->cbx += tocopy;
        space -= tocopy;
        c->cbuff[c->cbx] = 0;   /* terminate for benefit of strstr */
        s = strstr(c->cbuff, "\r\n\r\n");
        /* this next line is so that we talk to NCSA 1.5 which blatantly breaks 
           the http specifaction */
        if (!s) {
            s = strstr(c->cbuff, "\n\n");
            l = 2;
