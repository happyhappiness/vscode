void ap_init_scoreboard(void *shared_score)
{
    char *more_storage;
    int i;

    ap_calc_scoreboard_size();
    ap_scoreboard_image =
        calloc(1, sizeof(scoreboard) + server_limit * sizeof(worker_score *) +
               server_limit * lb_limit * sizeof(lb_score *));
    more_storage = shared_score;
    ap_scoreboard_image->global = (global_score *)more_storage;
    more_storage += sizeof(global_score);
    ap_scoreboard_image->parent = (process_score *)more_storage;
    more_storage += sizeof(process_score) * server_limit;
    ap_scoreboard_image->servers =
        (worker_score **)((char*)ap_scoreboard_image + sizeof(scoreboard));
    for (i = 0; i < server_limit; i++) {
        ap_scoreboard_image->servers[i] = (worker_score *)more_storage;
        more_storage += thread_limit * sizeof(worker_score);
    }
    if (lb_limit) {
        ap_scoreboard_image->balancers = (lb_score *)more_storage;
        more_storage += lb_limit * sizeof(lb_score);
    }
    ap_assert(more_storage == (char*)shared_score + scoreboard_size);
    ap_scoreboard_image->global->server_limit = server_limit;
    ap_scoreboard_image->global->thread_limit = thread_limit;
    ap_scoreboard_image->global->lb_limit     = lb_limit;
}