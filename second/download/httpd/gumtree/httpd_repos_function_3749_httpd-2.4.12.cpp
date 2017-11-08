void add_worker()
{
    int thread_slot;
    int stacksize = ap_thread_stacksize == 0 ? 128*1024 : ap_thread_stacksize;

    /* Find a free thread slot */
    for (thread_slot=0; thread_slot < HARD_THREAD_LIMIT; thread_slot++) {
        if (ap_scoreboard_image->servers[child_slot][thread_slot].status == SERVER_DEAD) {
            ap_scoreboard_image->servers[child_slot][thread_slot].status = SERVER_STARTING;
            ap_scoreboard_image->servers[child_slot][thread_slot].tid =
                _beginthread(worker_main, NULL, stacksize, (void *)thread_slot);
            break;
        }
    }
}