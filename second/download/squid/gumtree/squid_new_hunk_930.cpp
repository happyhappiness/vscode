    // AsyncJob API
    virtual void start();
    virtual bool doneAll() const { return false; } /// not done until mustStop

    bool usedDynamicRules();
    void check();
};

} // namespace Adaptation

#endif /* SQUID_ADAPTATION__ACCESS_CHECK_H */

