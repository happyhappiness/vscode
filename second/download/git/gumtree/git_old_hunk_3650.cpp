			show_tagger(buf + offset + 7,
				    new_offset - offset - 7, rev);
		offset = new_offset;
	}

	if (offset < size)
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

static void show_setup_revisions_tweak(struct rev_info *rev,
				       struct setup_revision_opt *opt)
{
