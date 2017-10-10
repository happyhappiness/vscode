	} else {
		fputs(name, fp);
	}
	fputc(terminator, fp);
}

void write_name_quotedpfx(const char *pfx, size_t pfxlen,
			  const char *name, FILE *fp, int terminator)
{
	int needquote = 0;

	if (terminator) {
		needquote = next_quote_pos(pfx, pfxlen) < pfxlen
			|| name[next_quote_pos(name, -1)];
	}
	if (needquote) {
		fputc('"', fp);
		quote_c_style_counted(pfx, pfxlen, NULL, fp, 1);
		quote_c_style(name, NULL, fp, 1);
		fputc('"', fp);
	} else {
		fwrite(pfx, pfxlen, 1, fp);
		fputs(name, fp);
	}
	fputc(terminator, fp);
}

void write_name_quoted_relative(const char *name, const char *prefix,
				FILE *fp, int terminator)
{
	struct strbuf sb = STRBUF_INIT;

	name = relative_path(name, prefix, &sb);
