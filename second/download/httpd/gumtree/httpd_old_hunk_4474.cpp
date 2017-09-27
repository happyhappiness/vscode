    int pid;

    if (slot + 1 > retained->max_daemons_limit) {
        retained->max_daemons_limit = slot + 1;
    }

    if (one_process) {
        my_bucket = &all_buckets[0];

        set_signals();
        event_note_child_started(slot, getpid());
        child_main(slot, 0);
