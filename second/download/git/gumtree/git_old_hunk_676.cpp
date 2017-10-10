	if (!default_refs) {
		fprintf(stderr, "notice: No default references\n");
		show_unreachable = 0;
	}
}

static int fsck_loose(const unsigned char *sha1, const char *path, void *data)
{
	if (fsck_sha1(sha1))
		errors_found |= ERROR_OBJECT;
	return 0;
}

static int fsck_cruft(const char *basename, const char *path, void *data)
{
