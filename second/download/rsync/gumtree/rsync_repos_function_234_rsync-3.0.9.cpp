NORETURN void _exit_cleanup(int code, const char *file, int line)
{
	static int switch_step = 0;
	static int exit_code = 0, exit_line = 0;
	static const char *exit_file = NULL;
	static int unmodified_code = 0;

	SIGACTION(SIGUSR1, SIG_IGN);
	SIGACTION(SIGUSR2, SIG_IGN);

	if (exit_code) { /* Preserve first exit info when recursing. */
		code = exit_code;
		file = exit_file;
		line = exit_line;
	}

	/* If this is the exit at the end of the run, the server side
	 * should not attempt to output a message (see log_exit()). */
	if (am_server && code == 0)
		am_server = 2;

	/* Some of our actions might cause a recursive call back here, so we
	 * keep track of where we are in the cleanup and never repeat a step. */
	switch (switch_step) {
#include "case_N.h" /* case 0: */
		switch_step++;

		exit_code = unmodified_code = code;
		exit_file = file;
		exit_line = line;

		if (verbose > 3) {
			rprintf(FINFO,
				"[%s] _exit_cleanup(code=%d, file=%s, line=%d): entered\n",
				who_am_i(), code, file, line);
		}

		/* FALLTHROUGH */
#include "case_N.h"
		switch_step++;

		if (cleanup_child_pid != -1) {
			int status;
			int pid = wait_process(cleanup_child_pid, &status, WNOHANG);
			if (pid == cleanup_child_pid) {
				status = WEXITSTATUS(status);
				if (status > code)
					code = exit_code = status;
			}
		}

		/* FALLTHROUGH */
#include "case_N.h"
		switch_step++;

		if (cleanup_got_literal && cleanup_fname && cleanup_new_fname
		 && keep_partial && handle_partial_dir(cleanup_new_fname, PDIR_CREATE)) {
			const char *fname = cleanup_fname;
			cleanup_fname = NULL;
			if (cleanup_fd_r != -1)
				close(cleanup_fd_r);
			if (cleanup_fd_w != -1) {
				flush_write_file(cleanup_fd_w);
				close(cleanup_fd_w);
			}
			finish_transfer(cleanup_new_fname, fname, NULL, NULL,
					cleanup_file, 0, !partial_dir);
		}

		/* FALLTHROUGH */
#include "case_N.h"
		switch_step++;

		if (!code || am_server || am_receiver)
			io_flush(FULL_FLUSH);

		/* FALLTHROUGH */
#include "case_N.h"
		switch_step++;

		if (cleanup_fname)
			do_unlink(cleanup_fname);
		if (code)
			kill_all(SIGUSR1);
		if (cleanup_pid && cleanup_pid == getpid()) {
			char *pidf = lp_pid_file();
			if (pidf && *pidf)
				unlink(lp_pid_file());
		}

		if (code == 0) {
			if (io_error & IOERR_DEL_LIMIT)
				code = exit_code = RERR_DEL_LIMIT;
			if (io_error & IOERR_VANISHED)
				code = exit_code = RERR_VANISHED;
			if (io_error & IOERR_GENERAL || got_xfer_error)
				code = exit_code = RERR_PARTIAL;
		}

		if (code || am_daemon || (logfile_name && (am_server || !verbose)))
			log_exit(code, file, line);

		/* FALLTHROUGH */
#include "case_N.h"
		switch_step++;

		if (verbose > 2) {
			rprintf(FINFO,
				"[%s] _exit_cleanup(code=%d, file=%s, line=%d): "
				"about to call exit(%d)\n",
				who_am_i(), unmodified_code, file, line, code);
		}

		/* FALLTHROUGH */
#include "case_N.h"
		switch_step++;

		if (am_server && code)
			msleep(100);
		close_all();

		/* FALLTHROUGH */
	default:
		break;
	}

	exit(code);
}