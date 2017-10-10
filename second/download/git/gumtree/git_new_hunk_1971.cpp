		fwrite(buf + offset, size - offset, 1, stdout);
	free(buf);
	return 0;
}

static int show_tree_object(const unsigned char *sha1,
		struct strbuf *base,
		const char *pathname, unsigned mode, int stage, void *context)
{
	printf("%s%s\n", pathname, S_ISDIR(mode) ? "/" : "");
	return 0;
}

