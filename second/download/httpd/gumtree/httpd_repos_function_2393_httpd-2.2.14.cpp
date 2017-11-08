static void startup_workers(int number_to_start)
{
    int i;

    for (i = 0; number_to_start && i < ap_threads_limit; ++i) {
        if (ap_scoreboard_image->servers[0][i].status != WORKER_DEAD) {
            continue;
        }
        if (make_child(ap_server_conf, i) < 0) {
            break;
        }
        --number_to_start;
    }
}