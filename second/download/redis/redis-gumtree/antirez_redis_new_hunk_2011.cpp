            if (start == -1) start = j;
        }
        if (start != -1 && (!bit || j == REDIS_CLUSTER_SLOTS-1)) {
            if (bit && j == REDIS_CLUSTER_SLOTS-1) j++;

            if (start == j-1) {
                ci = sdscatprintf(ci," %d",start);
