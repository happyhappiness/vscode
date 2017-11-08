static const char *set_child_per_uid(cmd_parms *cmd, void *dummy, const char *u,
                                     const char *g, const char *num)
{
    int i;
    int max_this_time = atoi(num) + curr_child_num;
    

    for (i = curr_child_num; i < max_this_time; i++, curr_child_num++) {
        if (i > num_daemons) {
            return "Trying to use more child ID's than NumServers.  Increase "
                   "NumServers in your config file.";
        }
    
        child_info_table[i].uid = ap_uname2id(u);
        child_info_table[i].gid = ap_gname2id(g); 

#ifndef BIG_SECURITY_HOLE
        if (child_info_table[i].uid == 0 || child_info_table[i].gid == 0) {
            return "Assigning root user/group to a child.";
        }
#endif
    }
    return NULL;
}