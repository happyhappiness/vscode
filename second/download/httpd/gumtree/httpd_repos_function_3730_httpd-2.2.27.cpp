static void mixer(apr_random_t *g,pid_t pid)
{
    unsigned char *H = H_current(g);

    /* mix the PID into the current H */
    mix_pid(g,H,pid);
    /* if we are in waiting, then also mix into main H */
    if (H != g->H)
        mix_pid(g,g->H,pid);
    /* change order of pool mixing for good measure - note that going
       backwards is much better than going forwards */
    --g->generation;
    /* blow away any lingering randomness */
    g->random_bytes = 0;
}