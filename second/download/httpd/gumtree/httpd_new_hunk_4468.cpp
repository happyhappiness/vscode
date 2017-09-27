    ap_scoreboard_image->parent[slot].pid = pid;
    ap_run_child_status(ap_server_conf,
                        ap_scoreboard_image->parent[slot].pid,
                        retained->my_generation, slot, MPM_CHILD_STARTED);
}

static const char *event_get_name(void)
{
    return "event";
}

/* a clean exit from a child with proper cleanup */
