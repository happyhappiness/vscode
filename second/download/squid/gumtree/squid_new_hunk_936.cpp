
    /// record the start of an ICAP processing interval
    void start(const char *context);
    /// note the end of an ICAP processing interval
    void stop(const char *context);

    /// the total time of all ICAP processing intervals
    /// \param[out] total time taken for all ICAP processing
    void processingTime(struct timeval &total) const;

    String rfc931; ///< the username from ident
#if USE_OPENSSL
    String ssluser; ///< the username from SSL
#endif
    LogTags logType; ///< the squid request status (TCP_MISS etc)

    String log_uri; ///< the request uri
    size_t req_sz; ///< the request size

private:
    void currentTime(struct timeval &) const; ///< time since current start or zero

    timeval currentStart; ///< when the current processing interval started
    struct timeval pastTime; ///< sum of closed processing interval durations
    int concurrencyLevel; ///< number of concurrent processing threads
};

} // namespace Icap
} // namespace Adaptation

