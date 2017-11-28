void
log_trace_done()
{
    fclose(tracefp);
    tracefp = NULL;
}