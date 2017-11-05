static apr_status_t worker_note_child_killed(int childnum)
{
    ap_scoreboard_image->parent[childnum].pid = 0;
    return APR_SUCCESS;
}