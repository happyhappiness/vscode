         * children which will then bind to another CPU.
         */
        int status = bindprocessor(BINDPROCESS, (int) getpid(),
                                   PROCESSOR_CLASS_ANY);
        if (status != OK)
            ap_log_error(APLOG_MARK, APLOG_DEBUG, errno,
                         ap_server_conf, APLOGNO(00482)
                         "processor unbind failed");
#endif
        RAISE_SIGSTOP(MAKE_CHILD);

        apr_signal(SIGTERM, just_die);
        child_main(slot);
        /* NOTREACHED */
    }
    /* else */
    if (ap_scoreboard_image->parent[slot].pid != 0) {
        /* This new child process is squatting on the scoreboard
         * entry owned by an exiting child process, which cannot
         * exit until all active requests complete.
         */
        event_note_child_lost_slot(slot, pid);
    }
    ap_scoreboard_image->parent[slot].quiescing = 0;
    ap_scoreboard_image->parent[slot].not_accepting = 0;
    event_note_child_started(slot, pid);
    return 0;
}

/* start up a bunch of children */
static void startup_children(int number_to_start)
{
