static int oom(int unused)
{
    static int called = 0;

    /* be careful to call exit() only once */
    if (!called) {
        called = 1;
        exit(1);
    }
    return APR_ENOMEM;
}