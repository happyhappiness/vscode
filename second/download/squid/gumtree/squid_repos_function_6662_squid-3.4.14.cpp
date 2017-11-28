void
log_trace_init(char *fn)
{
    tracefp = fopen(fn, "a+");

    if (!tracefp) {
        perror("log_trace_init");
        exit(1);
    }
}