
	if (tmpdir) {
		args[ac++] = "--temp-dir";
		args[ac++] = tmpdir;
	}

	if (compare_dest && am_sender) {
		/* the server only needs this option if it is not the sender,
		 *   and it may be an older version that doesn't know this
		 *   option, so don't send it if client is the sender.
		 */
		args[ac++] = link_dest ? "--link-dest" : "--compare-dest";
		args[ac++] = compare_dest;
	}

	if (files_from && (!am_sender || remote_filesfrom_file)) {
		if (remote_filesfrom_file) {
			args[ac++] = "--files-from";
			args[ac++] = remote_filesfrom_file;
			if (eol_nulls)
				args[ac++] = "--from0";
		} else {
			args[ac++] = "--files-from=-";
			args[ac++] = "--from0";
		}
	}

	*argc = ac;
	return;

    oom:
	out_of_memory("server_options");
}

/**
 * Return the position of a ':' IF it is not part of a filename (i.e. as
 * long as it doesn't occur after a slash.
 */
char *find_colon(char *s)
{
	char *p, *p2;

	p = strchr(s,':');
	if (!p)
		return NULL;

	/* now check to see if there is a / in the string before the : - if there is then
	   discard the colon on the assumption that the : is part of a filename */
	p2 = strchr(s,'/');
	if (p2 && p2 < p)
		return NULL;

	return p;
}
