    void clean();

    /** resets mb preserving (or initializing if needed) memory buffer */
    void reset();

    /** unfirtunate hack to test if the buffer has been Init()ialized */
    int isNull();

    /**
     * calls snprintf, extends buffer if needed
     \note  we use Printf instead of printf so the compiler won't
     *      think we're calling the libc printf()
     */
    void Printf(const char *fmt,...) PRINTF_FORMAT_ARG2;

    /** vPrintf for other printf()'s to use */
    void vPrintf(const char *fmt, va_list ap);

    /**
     * freezes the object! and returns function to clear it up.
     *
     \retval free() function to be used.
     */
    FREE *freeFunc();

private:
    /**
     * private copy constructor and assignment operator generates
     * compiler errors if someone tries to copy/assign a MemBuf
     */
    MemBuf(const MemBuf& m) {assert(false);};

    MemBuf& operator= (const MemBuf& m) {assert(false); return *this;};

    void grow(mb_size_t min_cap);

public:
    /**
     \deprecated use space*() and content*() methods to access safely instead.
     * public, read-only.
     *
     \todo XXX: hide these members completely and remove 0-termination
     *          so that consume() does not need to memmove all the time
     */
    char *buf;          // available content
    mb_size_t size;     // used space, does not count 0-terminator

    /**
     * when grows: assert(new_capacity <= max_capacity)
     \deprecated Use interface function instead
     \todo XXX: make these private after converting memBuf*() functions to methods
     */
    mb_size_t max_capacity;

    /**
     * allocated space
     \deprecated Use interface function instead
     \todo XXX: make these private after converting memBuf*() functions to methods
     */
    mb_size_t capacity;

    unsigned stolen:1;      /* the buffer has been stolen for use by someone else */

#if 0

    unsigned valid:1;       /* to be used for debugging only! */
#endif

private:
    CBDATA_CLASS2(MemBuf);
};

#if _USE_INLINE_
#include "MemBuf.cci"
#endif

/** returns free() function to be used, _freezes_ the object! */
void memBufReport(MemBuf * mb);
/** pack content into a mem buf. */
void packerToMemInit(Packer * p, MemBuf * mb);

#endif /* SQUID_MEM_H */

