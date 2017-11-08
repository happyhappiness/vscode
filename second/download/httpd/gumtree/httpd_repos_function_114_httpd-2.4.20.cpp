int abort_on_oom(int rc)
{
    const char *buf = "Error: out of memory\n";
    int written, count = strlen(buf);
    do {
        written = write(STDERR_FILENO, buf, count);
        if (written == count)
            break;
        if (written > 0) {
            buf += written;
            count -= written;
        }
    } while (written >= 0 || errno == EINTR);
    abort();
    /* NOTREACHED */
    return 0;
}