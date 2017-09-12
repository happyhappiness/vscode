graph = sdscatprintf(graph,
        "%s - high %lu ms, low %lu ms (all time high %lu ms)\n", event,
        (unsigned long) max, (unsigned long) min, (unsigned long) ts->max);