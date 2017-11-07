void transport_verify_remote_names(int nr_heads, const char **heads)
{
	int i;

	for (i = 0; i < nr_heads; i++) {
		const char *local = heads[i];
		const char *remote = strrchr(heads[i], ':');

		if (*local == '+')
			local++;

		/* A matching refspec is okay.  */
		if (remote == local && remote[1] == '\0')
			continue;

		remote = remote ? (remote + 1) : local;
		if (check_refname_format(remote,
				REFNAME_ALLOW_ONELEVEL|REFNAME_REFSPEC_PATTERN))
			die("remote part of refspec is not a valid name in %s",
				heads[i]);
	}
}