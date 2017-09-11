    link->refcount--;
    if (link->refcount != 0) {
        if (ri) {
            /* TODO: run the callbacks list and rebind. */
        }
        return link; /* Other active users. */
    }
