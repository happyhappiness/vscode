    else 
#endif
    {
        /* A simple malloc will suffice */
        void *sb_mem = calloc(1, scoreboard_size);
        if (sb_mem == NULL) {
            ap_log_error(APLOG_MARK, APLOG_CRIT | APLOG_NOERRNO, 0, NULL,
                         "(%d)%s: cannot allocate scoreboard",
                         errno, strerror(errno));
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        ap_init_scoreboard(sb_mem);
    }
