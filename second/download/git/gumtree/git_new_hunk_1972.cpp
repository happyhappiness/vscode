			       find_unique_abbrev(sha1, abbrev),
			       size_text);
		} else
			printf("%06o %s %s\t", mode, type,
			       find_unique_abbrev(sha1, abbrev));
	}
	baselen = base->len;
	strbuf_addstr(base, pathname);
	write_name_quoted_relative(base->buf,
				   chomp_prefix ? ls_tree_prefix : NULL,
				   stdout, line_termination);
	strbuf_setlen(base, baselen);
	return retval;
}

int cmd_ls_tree(int argc, const char **argv, const char *prefix)
{
	unsigned char sha1[20];
