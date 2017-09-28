        else if (elapsed < 3600)
            snprintf(buf,sizeof(buf),"%dm",elapsed/60);
        else if (elapsed < 3600*24)
            snprintf(buf,sizeof(buf),"%dh",elapsed/3600);
        else
            snprintf(buf,sizeof(buf),"%dd",elapsed/(3600*24));
        sparklineSequenceAddSample(seq,ts->samples[i].latency,buf);
    }

    graph = sdscatprintf(graph,
        "%s - high %lu ms, low %lu ms (all time high %lu ms)\n", event,
        (unsigned long) max, (unsigned long) min, (unsigned long) ts->max);
    for (j = 0; j < LATENCY_GRAPH_COLS; j++)
