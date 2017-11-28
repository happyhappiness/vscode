
protected:
    // XXX: temporary method to replace "delete this" in jobs-in-transition.
    // Will be replaced with calls to mustStop() when transition is complete.
    void deleteThis(const char *aReason);

    void mustStop(const char *aReason); // force done() for a reason

    bool done() const; // the job is destroyed in callEnd() when done()

    virtual void start();
    virtual bool doneAll() const; // return true when done
    virtual void swanSong() {}; // perform internal cleanup
    virtual const char *status() const; // for debugging

public:
    // asynchronous call maintenance
    bool canBeCalled(AsyncCall &call) const;
    void callStart(AsyncCall &call);
    virtual void callException(const std::exception &e);
    virtual void callEnd();

protected:
    const char *stopReason; // reason for forcing done() to be true
    const char *typeName; // kid (leaf) class name, for debugging
    AsyncCall::Pointer inCall; // the asynchronous call being handled, if any
    const unsigned int id;

private:
    static unsigned int TheLastId;
};

#endif /* SQUID_ASYNC_JOB_H */
