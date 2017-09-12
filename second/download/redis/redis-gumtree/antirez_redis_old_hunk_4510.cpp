    va_start(ap, fmt);
    if (level >= server.verbosity) {
        char *c = ".-*";
        fprintf(fp,"%c ",c[level]);
        vfprintf(fp, fmt, ap);
        fprintf(fp,"\n");
        fflush(fp);
