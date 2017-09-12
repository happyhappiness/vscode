            "cluster_slots_ok:%d\r\n"
            "cluster_slots_pfail:%d\r\n"
            "cluster_slots_fail:%d\r\n"
            , statestr[server.cluster.state],
            slots_assigned,
            slots_ok,
            slots_pfail,
            slots_fail
        );
        addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
            (unsigned long)sdslen(info)));
