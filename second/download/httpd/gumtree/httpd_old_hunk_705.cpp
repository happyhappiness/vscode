    sconf->sd2 = socks[1];

    for (i = 0; i < num_daemons; i++) {
        if (u == child_info_table[i].uid && g == child_info_table[i].gid) {
            child_info_table[i].sd = sconf->sd;
            matching++;
        }
    }

    if (!matching) {
        return "Unable to find process with matching uid/gid.";
    }
