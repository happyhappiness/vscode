static int tloop_join(pid_t pid, const char *name)
{
	int tret;
	if (waitpid(pid, &tret, 0) < 0) {
		error_errno("%s process failed to wait", name);
		return 1;
	}
	if (!WIFEXITED(tret) || WEXITSTATUS(tret)) {
		error("%s process failed", name);
		return 1;
	}
	return 0;
}