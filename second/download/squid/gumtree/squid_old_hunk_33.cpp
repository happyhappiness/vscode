
    void callBack(const ServiceGroupPointer &g);
    bool isCandidate(AccessRule &r);

public:
    void checkCandidates();
    static void AccessCheckCallbackWrapper(int, void*);
    void noteAnswer(int answer);

protected:
    // AsyncJob API
    virtual void start();
    virtual bool doneAll() const { return false; } /// not done until mustStop

    void check();

private:
    CBDATA_CLASS2(AccessCheck);
};

