		src = dst->buf;
		len = dst->len;
	}
	return ret | ident_to_git(path, src, len, dst, ca.ident);
}

static int convert_to_working_tree_internal(const char *path, const char *src,
					    size_t len, struct strbuf *dst,
					    int normalizing)
{
	int ret = 0, ret_filter = 0;
	const char *filter = NULL;
