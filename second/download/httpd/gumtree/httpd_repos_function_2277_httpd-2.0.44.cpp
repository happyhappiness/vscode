void add_worker()
{
    int thread_slot;

    /* Find a free thread slot */
    for (thread_slot=0; thread_slot < HARD_THREAD_LIMIT; thread_slot++) {
        if (ap_scoreboard_image->servers[child_slot][thread_slot].status == SERVER_DEAD) {
            ap_scoreboard_image->servers[child_slot][thread_slot].status = SERVER_STARTING;
            ap_scoreboard_image->servers[child_slot][thread_slot].tid =
                _beginthread(worker_main, NULL, 128*1024, (void *)thread_slot);
            break;
        }
    }
}