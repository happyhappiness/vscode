{
        /* Write a very simple .gz header:
         */
        fprintf(s->file, "%c%c%c%c%c%c%c%c%c%c", gz_magic[0], gz_magic[1],
             Z_DEFLATED, 0 /*flags*/, 0,0,0,0 /*time*/, 0 /*xflags*/, OS_CODE);
        s->start = 10L;
        /* We use 10L instead of ftell(s->file) to because ftell causes an
         * fflush on some systems. This version of the library doesn't use
         * start anyway in write mode, so this initialization is not
         * necessary.
         */
    }