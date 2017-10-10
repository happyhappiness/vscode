			       find_unique_abbrev(sha1, abbrev),
			       size_text);
		} else
			printf("%06o %s %s\t", mode, type,
			       find_unique_abbrev(sha1, abbrev));
	}
	write_name_quotedpfx(base + chomp_prefix, baselen - chomp_prefix,
			  pathname, stdout, line_termination);
	return retval;
}

int cmd_ls_tree(int argc, const char **argv, const char *prefix)
{
	unsigned char sha1[20];
