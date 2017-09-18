        }

        pid_buffer[i] = ps_record->pid;
    }

    /* up_time in seconds */
    up_time = (apr_uint32_t) ((nowtime -
                               ap_scoreboard_image->global->restart_time)
                              / APR_USEC_PER_SEC);

    if (!short_report) {
        ap_rputs(DOCTYPE_HTML_3_2
                 "<html><head>\n<title>Apache Status</title>\n</head><body>\n",
                 r);
        ap_rputs("<h1>Apache Server Status for ", r);
