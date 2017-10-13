static void flush_rewritten_pending(void) {
	struct strbuf buf = STRBUF_INIT;
	unsigned char newsha1[20];
	FILE *out;

	if (strbuf_read_file(&buf, rebase_path_rewritten_pending(), 82) > 0 &&
			!get_sha1("HEAD", newsha1) &&
			(out = fopen(rebase_path_rewritten_list(), "a"))) {
		char *bol = buf.buf, *eol;

		while (*bol) {
			eol = strchrnul(bol, '\n');
			fprintf(out, "%.*s %s\n", (int)(eol - bol),
					bol, sha1_to_hex(newsha1));
			if (!*eol)
				break;
			bol = eol + 1;
		}
		fclose(out);
		unlink(rebase_path_rewritten_pending());
	}
	strbuf_release(&buf);
}