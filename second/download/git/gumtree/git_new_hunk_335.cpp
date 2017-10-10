			     struct expand_data *data)
{
	struct object_context ctx;
	int flags = opt->follow_symlinks ? GET_SHA1_FOLLOW_SYMLINKS : 0;
	enum follow_symlinks_result result;

	result = get_sha1_with_context(obj_name, flags, data->oid.hash, &ctx);
	if (result != FOUND) {
		switch (result) {
		case MISSING_OBJECT:
			printf("%s missing\n", obj_name);
			break;
		case DANGLING_SYMLINK:
