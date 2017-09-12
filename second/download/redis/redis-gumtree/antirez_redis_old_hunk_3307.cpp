            ci = sdscatprintf(ci,"- ");

        /* Latency from the POV of this node, link status */
        ci = sdscatprintf(ci,"%ld %ld %s\n",
            (long) node->ping_sent,
            (long) node->pong_received,
            node->link ? "connected" : "disconnected");
    }
    dictReleaseIterator(di);
    return ci;
}
