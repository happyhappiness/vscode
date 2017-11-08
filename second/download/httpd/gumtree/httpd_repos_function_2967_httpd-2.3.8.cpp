static int abort_on_oom(int retcode)
{
    write(STDERR_FILENO, OOM_MESSAGE, strlen(OOM_MESSAGE));
    abort();
    return retcode; /* unreachable, hopefully. */
}