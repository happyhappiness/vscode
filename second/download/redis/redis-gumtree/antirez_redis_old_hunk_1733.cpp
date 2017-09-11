            snprintf(buf,sizeof(buf),"%dh",elapsed/3600);
        else
            snprintf(buf,sizeof(buf),"%dd",elapsed/(3600*24));
        label = zstrdup(buf);
        sparklineSequenceAddSample(seq,ts->samples[i].latency,label);
    }

    graph = sdscatprintf(graph,
