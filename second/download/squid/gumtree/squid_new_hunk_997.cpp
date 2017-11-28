
    /// abnormal transaction termination; reason is for debugging only
    virtual void abortAll(const char *reason) = 0;

    /// abnormal data transfer termination
    /// \retval true the transaction will be terminated (abortAll called)
    /// \reval false the transaction will survive
    virtual bool abortOnData(const char *reason);

    /// a hack to reach HttpStateData::orignal_request
    virtual  HttpRequest *originalRequest();

#if USE_ADAPTATION
