static int got_sha1(const char *hex, unsigned char *sha1)
{
	struct object *o;
	int we_knew_they_have = 0;

	if (get_sha1_hex(hex, sha1))
		die("git upload-pack: expected SHA1 object, got '%s'", hex);
	if (!has_sha1_file(sha1))
		return -1;

	o = parse_object(sha1);
	if (!o)
		die("oops (%s)", sha1_to_hex(sha1));
	if (o->type == OBJ_COMMIT) {
		struct commit_list *parents;
		struct commit *commit = (struct commit *)o;
		if (o->flags & THEY_HAVE)
			we_knew_they_have = 1;
		else
			o->flags |= THEY_HAVE;
		if (!oldest_have || (commit->date < oldest_have))
			oldest_have = commit->date;
		for (parents = commit->parents;
		     parents;
		     parents = parents->next)
			parents->item->object.flags |= THEY_HAVE;
	}
	if (!we_knew_they_have) {
		add_object_array(o, NULL, &have_obj);
		return 1;
	}
	return 0;
}