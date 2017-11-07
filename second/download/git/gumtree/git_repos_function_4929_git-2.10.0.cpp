static int stgit_patch_to_mail(FILE *out, FILE *in, int keep_cr)
{
	struct strbuf sb = STRBUF_INIT;
	int subject_printed = 0;

	while (!strbuf_getline_lf(&sb, in)) {
		const char *str;

		if (str_isspace(sb.buf))
			continue;
		else if (skip_prefix(sb.buf, "Author:", &str))
			fprintf(out, "From:%s\n", str);
		else if (starts_with(sb.buf, "From") || starts_with(sb.buf, "Date"))
			fprintf(out, "%s\n", sb.buf);
		else if (!subject_printed) {
			fprintf(out, "Subject: %s\n", sb.buf);
			subject_printed = 1;
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