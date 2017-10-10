	} else {
		fputs(name, fp);
	}
	fputc(terminator, fp);
}

void write_name_quoted_relative(const char *name, const char *prefix,
				FILE *fp, int terminator)
{
	struct strbuf sb = STRBUF_INIT;

	name = relative_path(name, prefix, &sb);
