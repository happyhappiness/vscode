static void rewrite_rand_init(void)
{
    if (!rewrite_rand_init_done) {
        srand((unsigned)(getpid()));
        rewrite_rand_init_done = 1;
    }
    return;
}