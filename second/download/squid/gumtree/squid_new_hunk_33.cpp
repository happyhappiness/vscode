
    void callBack(const ServiceGroupPointer &g);
    bool isCandidate(AccessRule &r);

public:
    void checkCandidates();
    static void AccessCheckCallbackWrapper(allow_t, void*);
    void noteAnswer(allow_t answer);

protected:
    // AsyncJob API
    virtual void start();
    virtual bool doneAll() const { return false; } /// not done until mustStop

    bool usedDynamicRules();
    void check();

private:
    CBDATA_CLASS2(AccessCheck);
};

