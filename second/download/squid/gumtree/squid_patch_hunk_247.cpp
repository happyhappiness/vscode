 SQUIDCEXTERN int storeClientIsThisAClient(store_client * sc, void *someClient);
 
 
 SQUIDCEXTERN const char *getMyHostname(void);
 SQUIDCEXTERN const char *uniqueHostname(void);
 SQUIDCEXTERN void safeunlink(const char *path, int quiet);
-SQUIDCEXTERN void death(int sig);
-SQUIDCEXTERN void fatal(const char *message);
-SQUIDCEXTERN void fatalf(const char *fmt,...) PRINTF_FORMAT_ARG1;
-SQUIDCEXTERN void fatal_dump(const char *message);
-SQUIDCEXTERN void sigusr2_handle(int sig);
-SQUIDCEXTERN void sig_child(int sig);
+
+#include "fatal.h"
+void death(int sig);
+void sigusr2_handle(int sig);
+void sig_child(int sig);
+void sig_shutdown(int sig); ///< handles shutdown notifications from kids
 SQUIDCEXTERN void leave_suid(void);
 SQUIDCEXTERN void enter_suid(void);
 SQUIDCEXTERN void no_suid(void);
 SQUIDCEXTERN void writePidFile(void);
 SQUIDCEXTERN void setSocketShutdownLifetimes(int);
 SQUIDCEXTERN void setMaxFD(void);
 SQUIDCEXTERN void setSystemLimits(void);
-SQUIDCEXTERN void squid_signal(int sig, SIGHDLR *, int flags);
+extern void squid_signal(int sig, SIGHDLR *, int flags);
 SQUIDCEXTERN pid_t readPidFile(void);
 SQUIDCEXTERN void keepCapabilities(void);
-
-/* AYJ debugs function to show locations being reset with memset() */
-SQUIDCEXTERN void *xmemset(void *dst, int, size_t);
+SQUIDCEXTERN void BroadcastSignalIfAny(int& sig);
+/// whether the current process is the parent of all other Squid processes
+SQUIDCEXTERN bool IamMasterProcess();
+/**
+    whether the current process is dedicated to doing things that only
+    a single process should do, such as PID file maintenance and WCCP
+*/
+SQUIDCEXTERN bool IamPrimaryProcess();
+/// whether the current process coordinates worker processes
+SQUIDCEXTERN bool IamCoordinatorProcess();
+/// whether the current process handles HTTP transactions and such
+SQUIDCEXTERN bool IamWorkerProcess();
+/// whether the current process is dedicated to managing a cache_dir
+bool IamDiskProcess();
+/// Whether we are running in daemon mode
+SQUIDCEXTERN bool InDaemonMode(); // try using specific Iam*() checks above first
+/// Whether there should be more than one worker process running
+SQUIDCEXTERN bool UsingSmp(); // try using specific Iam*() checks above first
+/// number of Kid processes as defined in src/ipc/Kid.h
+SQUIDCEXTERN int NumberOfKids();
+/// a string describing this process roles such as worker or coordinator
+String ProcessRoles();
+SQUIDCEXTERN int DebugSignal;
 
 SQUIDCEXTERN void debug_trap(const char *);
 SQUIDCEXTERN void logsFlush(void);
 SQUIDCEXTERN const char *checkNullString(const char *p);
 
 SQUIDCEXTERN void squid_getrusage(struct rusage *r);
