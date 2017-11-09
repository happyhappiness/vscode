static int log_ref_setup(struct files_ref_store *refs,
			 const char *refname, int force_create,
			 int *logfd, struct strbuf *err)
{
	struct strbuf logfile_sb = STRBUF_INIT;
	char *logfile;

	files_reflog_path(refs, &logfile_sb, refname);
	logfile = strbuf_detach(&logfile_sb, NULL);

	if (force_create || should_autocreate_reflog(refname)) {
		if (raceproof_create_file(logfile, open_or_create_logfile, logfd)) {
			if (errno == ENOENT)
				strbuf_addf(err, "unable to create directory for '%s': "
					    "%s", logfile, strerror(errno));
			else if (errno == EISDIR)
				strbuf_addf(err, "there are still logs under '%s'",
					    logfile);
			else
				strbuf_addf(err, "unable to append to '%s': %s",
					    logfile, strerror(errno));

			goto error;
		}
	} else {
		*logfd = open(logfile, O_APPEND | O_WRONLY, 0666);
		if (*logfd < 0) {
			if (errno == ENOENT || errno == EISDIR) {
				/*
				 * The logfile doesn't already exist,
				 * but that is not an error; it only
				 * means that we won't write log
				 * entries to it.
				 */
				;
			} else {
				strbuf_addf(err, "unable to append to '%s': %s",
					    logfile, strerror(errno));
				goto error;
			}
		}
	}

	if (*logfd >= 0)
		adjust_shared_perm(logfile);

	free(logfile);
	return 0;

error:
	free(logfile);
	return -1;
}