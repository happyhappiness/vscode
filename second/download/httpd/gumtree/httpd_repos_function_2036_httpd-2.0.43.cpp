int nlmUnloadSignaled()
{
    shutdown_pending = 1;

    while (wait_to_finish) {
        NXThreadYield();
    }

    return 0;
}