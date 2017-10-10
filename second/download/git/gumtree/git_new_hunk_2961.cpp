
	return 0;
}

static char *pack_bitmap_filename(struct packed_git *p)
{
	size_t len;

	if (!strip_suffix(p->pack_name, ".pack", &len))
		die("BUG: pack_name does not end in .pack");
	return xstrfmt("%.*s.bitmap", (int)len, p->pack_name);
}

static int open_pack_bitmap_1(struct packed_git *packfile)
{
	int fd;
	struct stat st;
