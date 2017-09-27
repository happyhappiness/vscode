         * request pool will have been deleted.  We set
         * r=NULL here to ensure that any dereference
         * of r that might be added later in this function
         * will result in a segfault immediately instead
         * of nondeterministic failures later.
         */
        r = NULL;
    }
    ap_update_child_status(c->sbh, SERVER_BUSY_WRITE, NULL);
    c->sbh = NULL;

    return APR_SUCCESS;
}




