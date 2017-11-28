SQUIDCEXTERN int storeClientIsThisAClient(store_client * sc, void *someClient);


SQUIDCEXTERN const char *getMyHostname(void);
SQUIDCEXTERN const char *uniqueHostname(void);
SQUIDCEXTERN void safeunlink(const char *path, int quiet);
SQUIDCEXTERN void death(int sig);
SQUIDCEXTERN void fatal(const char *message);
SQUIDCEXTERN void fatalf(const char *fmt,...) PRINTF_FORMAT_ARG1;
SQUIDCEXTERN void fatal_dump(const char *message);
SQUIDCEXTERN void sigusr2_handle(int sig);
SQUIDCEXTERN void sig_child(int sig);
SQUIDCEXTERN void leave_suid(void);
SQUIDCEXTERN void enter_suid(void);
SQUIDCEXTERN void no_suid(void);
SQUIDCEXTERN void writePidFile(void);
SQUIDCEXTERN void setSocketShutdownLifetimes(int);
SQUIDCEXTERN void setMaxFD(void);
SQUIDCEXTERN void setSystemLimits(void);
SQUIDCEXTERN void squid_signal(int sig, SIGHDLR *, int flags);
SQUIDCEXTERN pid_t readPidFile(void);
SQUIDCEXTERN void keepCapabilities(void);

/* AYJ debugs function to show locations being reset with memset() */
SQUIDCEXTERN void *xmemset(void *dst, int, size_t);

SQUIDCEXTERN void debug_trap(const char *);
SQUIDCEXTERN void logsFlush(void);
SQUIDCEXTERN const char *checkNullString(const char *p);

SQUIDCEXTERN void squid_getrusage(struct rusage *r);
