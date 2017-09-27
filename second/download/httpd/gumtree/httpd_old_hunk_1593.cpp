        ap_rvputs(r, "<dt>Restart Time: ",
                  ap_ht_time(r->pool,
                             ap_scoreboard_image->global->restart_time,
                             DEFAULT_TIME_FORMAT, 0),
                  "</dt>\n", NULL);
        ap_rprintf(r, "<dt>Parent Server Generation: %d</dt>\n",
                   (int)ap_my_generation);
        ap_rputs("<dt>Server uptime: ", r);
        show_time(r, up_time);
        ap_rputs("</dt>\n", r);
    }

    if (ap_extended_status) {
