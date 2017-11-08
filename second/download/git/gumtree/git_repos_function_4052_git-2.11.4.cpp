static int grep_source_load(struct grep_source *gs)
{
	if (gs->buf)
		return 0;

	switch (gs->type) {
	case GREP_SOURCE_FILE:
		return grep_source_load_file(gs);
	case GREP_SOURCE_SHA1:
		return grep_source_load_sha1(gs);
	case GREP_SOURCE_BUF:
		return gs->buf ? 0 : -1;
	}
	die("BUG: invalid grep_source type");
}