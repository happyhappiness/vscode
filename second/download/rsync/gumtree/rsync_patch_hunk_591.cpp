    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
 
 /*
-  logging and utility functions
-
+  Logging and utility functions.
   tridge, May 1998
+
+  Mapping to human-readable messages added by Martin Pool
+  <mbp@samba.org>, Oct 2000.
   */
 #include "rsync.h"
 
+static char *logfname;
 static FILE *logfile;
 static int log_error_fd = -1;
 
+int log_got_error=0;
+
+struct {
+        int code;
+        char const *name;
+} const rerr_names[] = {
+	{ RERR_SYNTAX     , "syntax or usage error" }, 
+	{ RERR_PROTOCOL   , "protocol incompatibility" }, 
+	{ RERR_FILESELECT , "errors selecting input/output files, dirs" }, 
+	{ RERR_UNSUPPORTED, "requested action not supported" }, 
+	{ RERR_SOCKETIO   , "error in socket IO" }, 
+	{ RERR_FILEIO     , "error in file IO" }, 
+	{ RERR_STREAMIO   , "error in rsync protocol data stream" }, 
+	{ RERR_MESSAGEIO  , "errors with program diagnostics" }, 
+	{ RERR_IPC        , "error in IPC code" }, 
+	{ RERR_SIGNAL     , "received SIGUSR1 or SIGINT" }, 
+	{ RERR_WAITCHILD  , "some error returned by waitpid()" }, 
+	{ RERR_MALLOC     , "error allocating core memory buffers" }, 
+	{ RERR_PARTIAL    , "partial transfer" }, 
+	{ RERR_TIMEOUT    , "timeout in data send/receive" }, 
+	{ RERR_CMD_FAILED , "remote shell failed" },
+	{ RERR_CMD_KILLED , "remote shell killed" },
+	{ RERR_CMD_RUN,     "remote command could not be run" },
+        { RERR_CMD_NOTFOUND, "remote command not found" },
+        { 0, NULL }
+};
+
+
+
+/*
+ * Map from rsync error code to name, or return NULL.
+ */
+static char const *rerr_name(int code)
+{
+        int i;
+        for (i = 0; rerr_names[i].name; i++) {
+                if (rerr_names[i].code == code)
+                        return rerr_names[i].name;
+        }
+        return NULL;
+}
+
+struct err_list {
+	struct err_list *next;
+	char *buf;
+	int len;
+	int written; /* how many bytes we have written so far */
+};
+
+static struct err_list *err_list_head;
+static struct err_list *err_list_tail;
+
+/* add an error message to the pending error list */
+static void err_list_add(int code, char *buf, int len)
+{
+	struct err_list *el;
+	el = (struct err_list *)malloc(sizeof(*el));
+	if (!el) exit_cleanup(RERR_MALLOC);
+	el->next = NULL;
+	el->buf = malloc(len+4);
+	if (!el->buf) exit_cleanup(RERR_MALLOC);
+	memcpy(el->buf+4, buf, len);
+	SIVAL(el->buf, 0, ((code+MPLEX_BASE)<<24) | len);
+	el->len = len+4;
+	el->written = 0;
+	if (err_list_tail) {
+		err_list_tail->next = el;
+	} else {
+		err_list_head = el;
+	}
+	err_list_tail = el;
+}
+
+
+/* try to push errors off the error list onto the wire */
+void err_list_push(void)
+{
+	if (log_error_fd == -1) return;
+
+	while (err_list_head) {
+		struct err_list *el = err_list_head;
+		int n = write(log_error_fd, el->buf+el->written, el->len - el->written);
+		/* don't check for an error if the best way of handling the error is
+		   to ignore it */
+		if (n == -1) break;
+		if (n > 0) {
+			el->written += n;
+		}
+		if (el->written == el->len) {
+			free(el->buf);
+			err_list_head = el->next;
+			if (!err_list_head) err_list_tail = NULL;
+			free(el);
+		}
+	}
+}
+
+
 static void logit(int priority, char *buf)
 {
-	if (logfile) {
+	if (logfname) {
+		if (!logfile)
+			log_open();
 		fprintf(logfile,"%s [%d] %s", 
 			timestring(time(NULL)), (int)getpid(), buf);
 		fflush(logfile);
 	} else {
 		syslog(priority, "%s", buf);
 	}
 }
 
-void log_open(void)
+void log_init(void)
 {
 	static int initialised;
 	int options = LOG_PID;
 	time_t t;
-	char *logf;
 
 	if (initialised) return;
 	initialised = 1;
 
 	/* this looks pointless, but it is needed in order for the
 	   C library on some systems to fetch the timezone info
 	   before the chroot */
 	t = time(NULL);
 	localtime(&t);
 
 	/* optionally use a log file instead of syslog */
-	logf = lp_log_file();
-	if (logf && *logf) {
-		extern int orig_umask;
-		int old_umask = umask(022 | orig_umask);
-		logfile = fopen(logf, "a");
-		umask(old_umask);
-		return;
+	logfname = lp_log_file();
+	if (logfname) {
+		if (*logfname) {
+			log_open();
+			return;
+		}
+		logfname = NULL;
 	}
 
 #ifdef LOG_NDELAY
 	options |= LOG_NDELAY;
 #endif
 
