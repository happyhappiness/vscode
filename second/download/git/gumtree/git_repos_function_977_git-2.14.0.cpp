static void child_err_spew(struct child_process *cmd, struct child_err *cerr)
{
	static void (*old_errfn)(const char *err, va_list params);

	old_errfn = get_error_routine();
	set_error_routine(fake_fatal);
	errno = cerr->syserr;

	switch (cerr->err) {
	case CHILD_ERR_CHDIR:
		error_errno("exec '%s': cd to '%s' failed",
			    cmd->argv[0], cmd->dir);
		break;
	case CHILD_ERR_DUP2:
		error_errno("dup2() in child failed");
		break;
	case CHILD_ERR_CLOSE:
		error_errno("close() in child failed");
		break;
	case CHILD_ERR_SIGPROCMASK:
		error_errno("sigprocmask failed restoring signals");
		break;
	case CHILD_ERR_ENOENT:
		error_errno("cannot run %s", cmd->argv[0]);
		break;
	case CHILD_ERR_SILENT:
		break;
	case CHILD_ERR_ERRNO:
		error_errno("cannot exec '%s'", cmd->argv[0]);
		break;
	}
	set_error_routine(old_errfn);
}