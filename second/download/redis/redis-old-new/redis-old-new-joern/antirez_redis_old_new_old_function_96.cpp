static void sdsOomAbort(void) {
    fprintf(stderr,"SDS: Out Of Memory (SDS_ABORT_ON_OOM defined)\n");
    abort();
}