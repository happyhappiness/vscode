     * caller of run().
     */
    void stop();

    int errcount;

    /// the [main program] loop running now; may be nil
    /// for simplicity, we assume there are no concurrent loops
    static EventLoop *Running;

private:
    /** setup state variables prior to running */
    void prepareToRun();

    /** check an individual engine */
    void checkEngine(AsyncEngine * engine, bool const primary);

    /** dispatch calls and events scheduled during checkEngine() */
    bool dispatchCalls();

    bool last_loop;
    typedef std::vector<AsyncEngine *> engine_vector;
    engine_vector engines;
    TimeEngine * timeService;
    AsyncEngine * primaryEngine;
    int loop_delay; /**< the delay to be given to the primary engine */
    bool error; /**< has an error occured in this loop */
    bool runOnceResult; /**< the result from runOnce */
