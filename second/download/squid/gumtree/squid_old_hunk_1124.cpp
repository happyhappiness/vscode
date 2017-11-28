    Kid(const String& kid_name);

    /// called when this kid got started, records PID
    void start(pid_t cpid);

    /// called when kid terminates, sets exiting status
    void stop(status_type exitStatus);

    /// returns true if tracking of kid is stopped
    bool running() const;

    /// returns true if master should restart this kid
    bool shouldRestart() const;
