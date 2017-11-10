static int add_one_ref(const char *path, const unsigned char *sha1, int flag, void *cb_data)
{
	struct object *object = parse_object_or_die(sha1, path);
	struct rev_info *revs = (struct rev_info *)cb_data;

	add_pending_object(revs, object, "");

	return 0;
}