    /* Common error when the user asks for an event we have no latency
     * information about. */
    addReplyErrorFormat(c,
        "No samples available for event '%s'", c->argv[2]->ptr);
}

