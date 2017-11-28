    void clean();

    /** resets mb preserving (or initializing if needed) memory buffer */
    void reset();

    /** unfirtunate hack to test if the buffer has been Init()ialized */
    int isNull() const;

    /**
     * freezes the object! and returns function to clear it up.
     *
     \retval free() function to be used.
     */
    FREE *freeFunc();

    /* Packable API */
    virtual void append(const char *c, int sz);
    virtual void vappendf(const char *fmt, va_list ap);

private:
    /**
     * private copy constructor and assignment operator generates
     * compiler errors if someone tries to copy/assign a MemBuf
     */
    MemBuf(const MemBuf &) {assert(false);}

    MemBuf& operator= (const MemBuf &) {assert(false); return *this;}

    void grow(mb_size_t min_cap);

public:
    /**
     \deprecated use space*() and content*() methods to access safely instead.
     * public, read-only.
     *
     * TODO: hide these members completely and remove 0-termination
     *          so that consume() does not need to memmove all the time
     */
    char *buf;          // available content
    mb_size_t size;     // used space, does not count 0-terminator

    /**
     * when grows: assert(new_capacity <= max_capacity)
     * \deprecated Use interface function instead
     * TODO: make these private after converting memBuf*() functions to methods
     */
    mb_size_t max_capacity;

    /**
     * allocated space
     * \deprecated Use interface function instead
     * TODO: make these private after converting memBuf*() functions to methods
     */
    mb_size_t capacity;

    unsigned stolen:1;      /* the buffer has been stolen for use by someone else */

#if 0

    unsigned valid:1;       /* to be used for debugging only! */
#endif
};

/** returns free() function to be used, _freezes_ the object! */
void memBufReport(MemBuf * mb);

#endif /* SQUID_MEMBUF_H */

