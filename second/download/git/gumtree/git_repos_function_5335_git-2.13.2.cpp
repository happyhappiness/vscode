static int hg_patch_to_mail(FILE *out, FILE *in, int keep_cr)
{
	struct strbuf sb = STRBUF_INIT;

	while (!strbuf_getline_lf(&sb, in)) {
		const char *str;

		if (skip_prefix(sb.buf, "# User ", &str))
			fprintf(out, "From: %s\n", str);
		else if (skip_prefix(sb.buf, "# Date ", &str)) {
			unsigned long timestamp;
			long tz, tz2;
			char *end;

			errno = 0;
			timestamp = strtoul(str, &end, 10);
			if (errno)
				return error(_("invalid timestamp"));

			if (!skip_prefix(end, " ", &str))
				return error(_("invalid Date line"));

			errno = 0;
			tz = strtol(str, &end, 10);
			if (errno)
				return error(_("invalid timezone offset"));

			if (*end)
				return error(_("invalid Date line"));

			/*
			 * mercurial's timezone is in seconds west of UTC,
			 * however git's timezone is in hours + minutes east of
			 * UTC. Convert it.
			 */
			tz2 = labs(tz) / 3600 * 100 + labs(tz) % 3600 / 60;
			if (tz > 0)
				tz2 = -tz2;

			fprintf(out, "Date: %s\n", show_date(timestamp, tz2, DATE_MODE(RFC2822)));
		} else if (starts_with(sb.buf, "# ")) {
			continue;
		} else {
			fprintf(out, "\n%s\n", sb.buf);
			break;
		}
	}

	strbuf_reset(&sb);
	while (strbuf_fread(&sb, 8192, in) > 0) {
		fwrite(sb.buf, 1, sb.len, out);
		strbuf_reset(&sb);
	}

	strbuf_release(&sb);
	return 0;
}