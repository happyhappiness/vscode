	if (check_ancestors(prefix))
		check_merge_bases(no_checkout);

	/* Create file BISECT_ANCESTORS_OK. */
	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (fd < 0)
		warning_errno("could not create file '%s'",
			      filename);
	else
		close(fd);
 done:
	free(filename);
}

