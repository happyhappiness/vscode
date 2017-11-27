 #include <sys/wait.h>
 
 #include <time.h>
 
 #include <unistd.h>
 
+#ifndef PREFIX
+# define PREFIX "/opt/" PACKAGE_NAME
+#endif
+
+#ifndef LOCALSTATEDIR
+# define LOCALSTATEDIR PREFIX "/var"
+#endif
+
 #ifndef COLLECTDMON_PIDFILE
 # define COLLECTDMON_PIDFILE LOCALSTATEDIR"/run/collectdmon.pid"
 #endif /* ! COLLECTDMON_PIDFILE */
 
 #ifndef WCOREDUMP
 # define WCOREDUMP(s) 0
 #endif /* ! WCOREDUMP */
 
 static int loop    = 0;
 static int restart = 0;
 
-static char  *pidfile      = NULL;
-static pid_t  collectd_pid = 0;
+static const char *pidfile      = NULL;
+static pid_t       collectd_pid = 0;
 
-static void exit_usage (char *name)
+__attribute__((noreturn))
+static void exit_usage (const char *name)
 {
 	printf ("Usage: %s <options> [-- <collectd options>]\n"
 
 			"\nAvailable options:\n"
 			"  -h         Display this help and exit.\n"
 			"  -c <path>  Path to the collectd binary.\n"
