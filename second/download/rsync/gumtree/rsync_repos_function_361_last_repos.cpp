void print_child_argv(const char *prefix, char **cmd)
{
	int cnt = 0;
	rprintf(FCLIENT, "%s ", prefix);
	for (; *cmd; cmd++) {
		/* Look for characters that ought to be quoted.  This
		* is not a great quoting algorithm, but it's
		* sufficient for a log message. */
		if (strspn(*cmd, "abcdefghijklmnopqrstuvwxyz"
			   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			   "0123456789"
			   ",.-_=+@/") != strlen(*cmd)) {
			rprintf(FCLIENT, "\"%s\" ", *cmd);
		} else {
			rprintf(FCLIENT, "%s ", *cmd);
		}
		cnt++;
	}
	rprintf(FCLIENT, " (%d args)\n", cnt);
}