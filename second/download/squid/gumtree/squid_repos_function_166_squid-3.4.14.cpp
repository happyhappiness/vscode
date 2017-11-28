static void
local_printfx(const char *msg,...)
{
    char prog[EDUI_MAXLEN], dbuf[EDUI_MAXLEN];
    size_t sz, x;
    va_list ap;

    if (edui_conf.program[0] == '\0')
        xstrncpy(prog, EDUI_PROGRAM_NAME, sizeof(prog));
    else
        xstrncpy(prog, edui_conf.program, sizeof(prog));

    if (msg == NULL) {
        /* FAIL */
        debug("local_printfx() FAILURE, no data.\n");
        return;
    }
    sz = sizeof(dbuf);
    va_start(ap, msg);
    x = vsnprintf(dbuf, sz, msg, ap);
    va_end(ap);
    if (x > 0) {
        dbuf[x] = '\0';
        ++x;
        fputs(dbuf, stdout);
        *(dbuf) = '\0';
    } else {
        /* FAIL */
        debug("local_printfx() FAILURE: %" PRIuSIZE "\n", x);
    }

    /* stdout needs to be flushed for it to work with Squid */
    fflush(stdout);
}