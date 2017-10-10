		strbuf_addch(&sb, '\n');
		fprintf(f, "%s", sb.buf);
	}
	strbuf_release(&sb);
}

void show_submodule_summary(FILE *f, const char *path,
		const char *line_prefix,
		unsigned char one[20], unsigned char two[20],
		unsigned dirty_submodule, const char *meta,
		const char *del, const char *add, const char *reset)
{
