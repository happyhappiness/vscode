int nlmUnloadSignaled(int wait)
{
    shutdown_pending = 1;

    if (wait) {
        while (wait_to_finish) {
            NXThreadYield();
        }
    }

    return 0;
}