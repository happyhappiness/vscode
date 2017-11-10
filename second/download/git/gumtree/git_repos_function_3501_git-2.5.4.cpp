static int grep_source_load_sha1(struct grep_source *gs)
{
	enum object_type type;

	grep_read_lock();
	gs->buf = read_sha1_file(gs->identifier, &type, &gs->size);
	grep_read_unlock();

	if (!gs->buf)
		return error(_("'%s': unable to read %s"),
			     gs->name,
			     sha1_to_hex(gs->identifier));
	return 0;
}