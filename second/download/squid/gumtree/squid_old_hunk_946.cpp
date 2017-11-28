    void startSending();
    void disableBypass(const char *reason, bool includeGroupBypass);

    void prepEchoing();
    void prepPartialBodyEchoing(uint64_t pos);
    void echoMore();

    virtual bool doneAll() const;
    virtual void swanSong();

    void stopReceiving();
    void stopSending(bool nicely);
