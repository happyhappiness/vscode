static int
child_stop(struct archive_read_filter *self, struct program_filter *state)
{
	/* Close our side of the I/O with the child. */
	if (state->child_stdin != -1) {
		close(state->child_stdin);
		state->child_stdin = -1;
	}
	if (state->child_stdout != -1) {
		close(state->child_stdout);
		state->child_stdout = -1;
	}

	if (state->child != 0) {
		/* Reap the child. */
		do {
			state->waitpid_return
			    = waitpid(state->child, &state->exit_status, 0);
		} while (state->waitpid_return == -1 && errno == EINTR);
#if defined(_WIN32) && !defined(__CYGWIN__)
		CloseHandle(state->child);
#endif
		state->child = 0;
	}

	if (state->waitpid_return < 0) {
		/* waitpid() failed?  This is ugly. */
		archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
		    "Child process exited badly");
		return (ARCHIVE_WARN);
	}

#if !defined(_WIN32) || defined(__CYGWIN__)
	if (WIFSIGNALED(state->exit_status)) {
#ifdef SIGPIPE
		/* If the child died because we stopped reading before
		 * it was done, that's okay.  Some archive formats
		 * have padding at the end that we routinely ignore. */
		/* The alternative to this would be to add a step
		 * before close(child_stdout) above to read from the
		 * child until the child has no more to write. */
		if (WTERMSIG(state->exit_status) == SIGPIPE)
			return (ARCHIVE_OK);
#endif
		archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
		    "Child process exited with signal %d",
		    WTERMSIG(state->exit_status));
		return (ARCHIVE_WARN);
	}
#endif /* !_WIN32 || __CYGWIN__ */

	if (WIFEXITED(state->exit_status)) {
		if (WEXITSTATUS(state->exit_status) == 0)
			return (ARCHIVE_OK);

		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC,
		    "Child process exited with status %d",
		    WEXITSTATUS(state->exit_status));
		return (ARCHIVE_WARN);
	}

	return (ARCHIVE_WARN);
}