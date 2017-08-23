static int
archive_write_shar_finish_entry(struct archive_write *a)
{
	const char *g, *p, *u;
	struct shar *shar;
	int ret;

	shar = (struct shar *)a->format_data;
	if (shar->entry == NULL)
		return (0);

	if (shar->dump) {
		/* Finish uuencoded data. */
		if (shar->has_data) {
			if (shar->outpos > 0)
				uuencode_line(a, shar, shar->outbuff,
				    shar->outpos);
			archive_strcat(&shar->work, "`\nend\n");
			archive_strcat(&shar->work, "SHAR_END\n");
		}
		/* Restore file mode, owner, flags. */
		/*
		 * TODO: Don't immediately restore mode for
		 * directories; defer that to end of script.
		 */
		archive_string_sprintf(&shar->work, "chmod %o ",
		    (unsigned int)(archive_entry_mode(shar->entry) & 07777));
		shar_quote(&shar->work, archive_entry_pathname(shar->entry), 1);
		archive_strcat(&shar->work, "\n");

		u = archive_entry_uname(shar->entry);
		g = archive_entry_gname(shar->entry);
		if (u != NULL || g != NULL) {
			archive_strcat(&shar->work, "chown ");
			if (u != NULL)
				shar_quote(&shar->work, u, 1);
			if (g != NULL) {
				archive_strcat(&shar->work, ":");
				shar_quote(&shar->work, g, 1);
			}
			archive_strcat(&shar->work, " ");
			shar_quote(&shar->work,
			    archive_entry_pathname(shar->entry), 1);
			archive_strcat(&shar->work, "\n");
		}

		if ((p = archive_entry_fflags_text(shar->entry)) != NULL) {
			archive_string_sprintf(&shar->work, "chflags %s ", p);
			shar_quote(&shar->work,
			    archive_entry_pathname(shar->entry), 1);
			archive_strcat(&shar->work, "\n");
		}

		/* TODO: restore ACLs */

	} else {
		if (shar->has_data) {
			/* Finish sed-encoded data:  ensure last line ends. */
			if (!shar->end_of_line)
				archive_strappend_char(&shar->work, '\n');
			archive_strcat(&shar->work, "SHAR_END\n");
		}
	}

	archive_entry_free(shar->entry);
	shar->entry = NULL;

	if (shar->work.length < 65536)
		return (ARCHIVE_OK);

	ret = __archive_write_output(a, shar->work.s, shar->work.length);
	if (ret != ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	archive_string_empty(&shar->work);

	return (ARCHIVE_OK);
}