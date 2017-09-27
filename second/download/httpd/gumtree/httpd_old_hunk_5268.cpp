        return result;
    }
    else {
        /*
         * We have just bound the connection to a different user and password
         * combination, which might be reused unintentionally next time this
         * connection is used from the connection pool. To ensure no confusion,
         * we mark the connection as unbound.
         */
        ldc->bound = 0;
    }

    /*
     * Get values for the provided attributes.
     */
    if (attrs) {
