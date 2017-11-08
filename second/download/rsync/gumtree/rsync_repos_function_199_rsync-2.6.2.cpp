void print_child_argv(char **cmd)
{
	rprintf(FINFO, "opening connection using ");
	for (; *cmd; cmd++) {
		/* Look for characters that ought to be quoted.  This
		* is not a great quoting algorithm, but it's
		* sufficient for a log message. */
		if (strspn(*cmd, "abcdefghijklmnopqrstuvwxyz"
			   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			   "0123456789"
			   ",.-_=+@/") != strlen(*cmd)) {
			rprintf(FINFO, "\"%s\" ", *cmd);
		} else {
			rprintf(FINFO, "%s ", *cmd);
		}
	}
	rprintf(FINFO, "\n");
}