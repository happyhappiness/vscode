ap_rvputs(r, "RestartTime: ",
                  ap_ht_time(r->pool,
                             ap_scoreboard_image->global->restart_time,
                             DEFAULT_TIME_FORMAT, 0),
                  "\n", NULL);