
	if (finish_command(&cp) || len < 0)
		die(_("stash failed"));
	else if (!len)		/* no changes */
		return -1;
	strbuf_setlen(&buffer, buffer.len-1);
	if (get_sha1(buffer.buf, stash))
		die(_("not a valid object: %s"), buffer.buf);
	return 0;
}

static void read_empty(unsigned const char *sha1, int verbose)
{
