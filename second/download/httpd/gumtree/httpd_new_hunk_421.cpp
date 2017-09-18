
static void check_restart(void *data)
{
    if (!restart_pending && !shutdown_pending) {
        int slot = (int)data;
        make_worker(slot);
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, NULL, 
            "spawning a new worker thread in slot %d", slot);
    }
}

/* start up a bunch of children */
static void startup_threads(int number_to_start)
