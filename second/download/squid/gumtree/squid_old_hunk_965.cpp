     *
     * \param handler   Handler to process the callback when its run
     * \param data  CBDATA for handler
     */
    void start(HttpRequest *request, AccessLogEntry::Pointer &al, AUTHCB *handler, void *data);

    char const * denyMessage(char const * const default_message = NULL);

    /** Possibly overrideable in future */
    void setDenyMessage(char const *);

    /** Possibly overrideable in future */
    char const * getDenyMessage();

    /**
     * Squid does not make assumptions about where the username is stored.
     * This function must return a pointer to a NULL terminated string to be used in logging the request.
     * The string should NOT be allocated each time this function is called.
     *
