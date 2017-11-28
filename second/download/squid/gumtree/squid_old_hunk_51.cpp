    void maybeAllocateHttpMsg();

    void handle100Continue();
    bool validate200Ok();
    void handle200Ok();
    void handle204NoContent();
    void handleUnknownScode();

    void bypassFailure();

    void startSending();
    void disableBypass(const char *reason, bool includeGroupBypass);

    void prepEchoing();
    void echoMore();

    virtual bool doneAll() const;
    virtual void swanSong();

    void stopReceiving();
