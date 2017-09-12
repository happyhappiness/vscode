ci = sdscatprintf(ci,"vars currentEpoch %llu last_vote_epoch %llu\n",
        (unsigned long long) server.cluster->currentEpoch,
        (unsigned long long) server.cluster->last_vote_epoch);