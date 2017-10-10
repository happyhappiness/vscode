 
 	argv_array_pushv(out, argv);
 	return out->argv;
 }
 
 #ifndef GIT_WINDOWS_NATIVE
-static int execv_shell_cmd(const char **argv)
+static int child_notifier = -1;
+
+enum child_errcode {
+	CHILD_ERR_CHDIR,
+	CHILD_ERR_DUP2,
+	CHILD_ERR_CLOSE,
+	CHILD_ERR_SIGPROCMASK,
+	CHILD_ERR_ENOENT,
+	CHILD_ERR_SILENT,
+	CHILD_ERR_ERRNO
+};
+
+struct child_err {
+	enum child_errcode err;
+	int syserr; /* errno */
+};
+
+static void child_die(enum child_errcode err)
+{
+	struct child_err buf;
+
+	buf.err = err;
+	buf.syserr = errno;
+
+	/* write(2) on buf smaller than PIPE_BUF (min 512) is atomic: */
+	xwrite(child_notifier, &buf, sizeof(buf));
+	_exit(1);
+}
+
+static void child_dup2(int fd, int to)
 {
-	struct argv_array nargv = ARGV_ARRAY_INIT;
-	prepare_shell_cmd(&nargv, argv);
-	trace_argv_printf(nargv.argv, "trace: exec:");
-	sane_execvp(nargv.argv[0], (char **)nargv.argv);
-	argv_array_clear(&nargv);
-	return -1;
+	if (dup2(fd, to) < 0)
+		child_die(CHILD_ERR_DUP2);
 }
-#endif
 
-#ifndef GIT_WINDOWS_NATIVE
-static int child_notifier = -1;
+static void child_close(int fd)
+{
+	if (close(fd))
+		child_die(CHILD_ERR_CLOSE);
+}
+
+static void child_close_pair(int fd[2])
+{
+	child_close(fd[0]);
+	child_close(fd[1]);
+}
+
+/*
+ * parent will make it look like the child spewed a fatal error and died
+ * this is needed to prevent changes to t0061.
+ */
+static void fake_fatal(const char *err, va_list params)
+{
+	vreportf("fatal: ", err, params);
+}
+
+static void child_error_fn(const char *err, va_list params)
+{
+	const char msg[] = "error() should not be called in child\n";
+	xwrite(2, msg, sizeof(msg) - 1);
+}
+
+static void child_warn_fn(const char *err, va_list params)
+{
+	const char msg[] = "warn() should not be called in child\n";
+	xwrite(2, msg, sizeof(msg) - 1);
+}
+
+static void NORETURN child_die_fn(const char *err, va_list params)
+{
+	const char msg[] = "die() should not be called in child\n";
+	xwrite(2, msg, sizeof(msg) - 1);
+	_exit(2);
+}
+
+/* this runs in the parent process */
+static void child_err_spew(struct child_process *cmd, struct child_err *cerr)
+{
+	static void (*old_errfn)(const char *err, va_list params);
+
+	old_errfn = get_error_routine();
+	set_error_routine(fake_fatal);
+	errno = cerr->syserr;
+
+	switch (cerr->err) {
+	case CHILD_ERR_CHDIR:
+		error_errno("exec '%s': cd to '%s' failed",
+			    cmd->argv[0], cmd->dir);
+		break;
+	case CHILD_ERR_DUP2:
+		error_errno("dup2() in child failed");
+		break;
+	case CHILD_ERR_CLOSE:
+		error_errno("close() in child failed");
+		break;
+	case CHILD_ERR_SIGPROCMASK:
+		error_errno("sigprocmask failed restoring signals");
+		break;
+	case CHILD_ERR_ENOENT:
+		error_errno("cannot run %s", cmd->argv[0]);
+		break;
+	case CHILD_ERR_SILENT:
+		break;
+	case CHILD_ERR_ERRNO:
+		error_errno("cannot exec '%s'", cmd->argv[0]);
+		break;
+	}
+	set_error_routine(old_errfn);
+}
 
-static void notify_parent(void)
+static void prepare_cmd(struct argv_array *out, const struct child_process *cmd)
 {
+	if (!cmd->argv[0])
+		die("BUG: command is empty");
+
+	/*
+	 * Add SHELL_PATH so in the event exec fails with ENOEXEC we can
+	 * attempt to interpret the command with 'sh'.
+	 */
+	argv_array_push(out, SHELL_PATH);
+
+	if (cmd->git_cmd) {
+		argv_array_push(out, "git");
+		argv_array_pushv(out, cmd->argv);
+	} else if (cmd->use_shell) {
+		prepare_shell_cmd(out, cmd->argv);
+	} else {
+		argv_array_pushv(out, cmd->argv);
+	}
+
 	/*
-	 * execvp failed.  If possible, we'd like to let start_command
-	 * know, so failures like ENOENT can be handled right away; but
-	 * otherwise, finish_command will still report the error.
+	 * If there are no '/' characters in the command then perform a path
+	 * lookup and use the resolved path as the command to exec.  If there
+	 * are no '/' characters or if the command wasn't found in the path,
+	 * have exec attempt to invoke the command directly.
 	 */
-	xwrite(child_notifier, "", 1);
+	if (!strchr(out->argv[1], '/')) {
+		char *program = locate_in_PATH(out->argv[1]);
+		if (program) {
+			free((char *)out->argv[1]);
+			out->argv[1] = program;
+		}
+	}
+}
+
+static char **prep_childenv(const char *const *deltaenv)
+{
+	extern char **environ;
+	char **childenv;
+	struct string_list env = STRING_LIST_INIT_DUP;
+	struct strbuf key = STRBUF_INIT;
+	const char *const *p;
+	int i;
+
+	/* Construct a sorted string list consisting of the current environ */
+	for (p = (const char *const *) environ; p && *p; p++) {
+		const char *equals = strchr(*p, '=');
+
+		if (equals) {
+			strbuf_reset(&key);
+			strbuf_add(&key, *p, equals - *p);
+			string_list_append(&env, key.buf)->util = (void *) *p;
+		} else {
+			string_list_append(&env, *p)->util = (void *) *p;
+		}
+	}
+	string_list_sort(&env);
+
+	/* Merge in 'deltaenv' with the current environ */
+	for (p = deltaenv; p && *p; p++) {
+		const char *equals = strchr(*p, '=');
+
+		if (equals) {
+			/* ('key=value'), insert or replace entry */
+			strbuf_reset(&key);
+			strbuf_add(&key, *p, equals - *p);
+			string_list_insert(&env, key.buf)->util = (void *) *p;
+		} else {
+			/* otherwise ('key') remove existing entry */
+			string_list_remove(&env, *p, 0);
+		}
+	}
+
+	/* Create an array of 'char *' to be used as the childenv */
+	childenv = xmalloc((env.nr + 1) * sizeof(char *));
+	for (i = 0; i < env.nr; i++)
+		childenv[i] = env.items[i].util;
+	childenv[env.nr] = NULL;
+
+	string_list_clear(&env, 0);
+	strbuf_release(&key);
+	return childenv;
+}
+
+struct atfork_state {
+#ifndef NO_PTHREADS
+	int cs;
+#endif
+	sigset_t old;
+};
+
+#ifndef NO_PTHREADS
+static void bug_die(int err, const char *msg)
+{
+	if (err) {
+		errno = err;
+		die_errno("BUG: %s", msg);
+	}
+}
+#endif
+
+static void atfork_prepare(struct atfork_state *as)
+{
+	sigset_t all;
+
+	if (sigfillset(&all))
+		die_errno("sigfillset");
+#ifdef NO_PTHREADS
+	if (sigprocmask(SIG_SETMASK, &all, &as->old))
+		die_errno("sigprocmask");
+#else
+	bug_die(pthread_sigmask(SIG_SETMASK, &all, &as->old),
+		"blocking all signals");
+	bug_die(pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &as->cs),
+		"disabling cancellation");
+#endif
 }
+
+static void atfork_parent(struct atfork_state *as)
+{
+#ifdef NO_PTHREADS
+	if (sigprocmask(SIG_SETMASK, &as->old, NULL))
+		die_errno("sigprocmask");
+#else
+	bug_die(pthread_setcancelstate(as->cs, NULL),
+		"re-enabling cancellation");
+	bug_die(pthread_sigmask(SIG_SETMASK, &as->old, NULL),
+		"restoring signal mask");
 #endif
+}
+#endif /* GIT_WINDOWS_NATIVE */
 
 static inline void set_cloexec(int fd)
 {
 	int flags = fcntl(fd, F_GETFD);
 	if (flags >= 0)
 		fcntl(fd, F_SETFD, flags | FD_CLOEXEC);
