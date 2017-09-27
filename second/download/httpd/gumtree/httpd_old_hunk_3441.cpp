            int status = ap_scoreboard_image->servers[child_num_arg][i].status;

            if (status != SERVER_GRACEFUL && status != SERVER_DEAD) {
                continue;
            }

            my_info = (proc_info *)malloc(sizeof(proc_info));
            if (my_info == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ALERT, errno, ap_server_conf,
                             "malloc: out of memory");
                clean_child_exit(APEXIT_CHILDFATAL);
            }
            my_info->pid = my_child_num;
            my_info->tid = i;
            my_info->sd = 0;

            /* We are creating threads right now */
            ap_update_child_status_from_indexes(my_child_num, i,
