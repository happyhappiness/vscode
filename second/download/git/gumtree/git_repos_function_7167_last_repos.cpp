static int fetch_native_store(FILE *fp,
			      const char *remote,
			      const char *remote_nick,
			      const char *refs,
			      int verbose, int force)
{
	char buffer[1024];
	int err = 0;

	sigchain_push_common(remove_keep_on_signal);
	atexit(remove_keep);

	while (fgets(buffer, sizeof(buffer), stdin)) {
		int len;
		char *cp;
		char *local_name;
		int single_force, not_for_merge;

		for (cp = buffer; *cp && !isspace(*cp); cp++)
			;
		if (*cp)
			*cp++ = 0;
		len = strlen(cp);
		if (len && cp[len-1] == '\n')
			cp[--len] = 0;
		if (!strcmp(buffer, "failed"))
			die("Fetch failure: %s", remote);
		if (!strcmp(buffer, "pack"))
			continue;
		if (!strcmp(buffer, "keep")) {
			char *od = get_object_directory();
			int len = strlen(od) + strlen(cp) + 50;
			keep = xmalloc(len);
			sprintf(keep, "%s/pack/pack-%s.keep", od, cp);
			continue;
		}

		local_name = find_local_name(cp, refs,
					     &single_force, &not_for_merge);
		if (!local_name)
			continue;
		err |= append_fetch_head(fp,
					 buffer, remote, cp, remote_nick,
					 local_name, not_for_merge,
					 verbose, force || single_force);
	}
	return err;
}