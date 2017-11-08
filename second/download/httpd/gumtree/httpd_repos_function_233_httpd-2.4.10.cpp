static int dav_fs_do_refresh(dav_lock_discovery *dp,
                             const dav_locktoken_list *ltl,
                             time_t new_time)
{
    int dirty = 0;

    for (; ltl != NULL; ltl = ltl->next) {
        if (dav_compare_locktoken(dp->locktoken, ltl->locktoken) == 0)
        {
            dp->f.timeout = new_time;
            dirty = 1;
            break;
        }
    }

    return dirty;
}