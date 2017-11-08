static void perform_idle_server_maintenance(void)
{
    int i;
    int free_length;
    int free_slots[MAX_SPAWN_RATE];
    int last_non_dead  = -1;

    /* initialize the free_list */
    free_length = 0;

    for (i = 0; i < ap_thread_limit; ++i) {
        if (ap_scoreboard_image->servers[0][i].tid == 0) {
            if (free_length < spawn_rate) {
                free_slots[free_length] = i;
                ++free_length;
            }
        }
        else {
            last_non_dead = i;
        }

        if (i >= ap_max_child_assigned && free_length >= spawn_rate) {
                 break;
        }
    }
    ap_max_child_assigned = last_non_dead + 1;

    if (free_length > 0) {
        for (i = 0; i < free_length; ++i) {
                make_worker(free_slots[i]);
        }
        /* the next time around we want to spawn twice as many if this
         * wasn't good enough, but not if we've just done a graceful
         */
        if (hold_off_on_exponential_spawning) {
            --hold_off_on_exponential_spawning;
        } else if (spawn_rate < MAX_SPAWN_RATE) {
            spawn_rate *= 2;
        }
    } else {
        spawn_rate = 1;
    }
}