static void htdbm_interrupted(void)
{
    htdbm_terminate(h);
    fprintf(stderr, "htdbm Interrupted !\n");
    exit(ERR_INTERRUPTED);
}