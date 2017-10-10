static struct commit_extra_header *read_commit_extra_header_lines(const char *buf, size_t len, const char **);

int save_commit_buffer = 1;

const char *commit_type = "commit";

struct commit *lookup_commit_reference_gently(const unsigned char *sha1,
					      int quiet)
{
	struct object *obj = deref_tag(parse_object(sha1), NULL, 0);

	if (!obj)
		return NULL;
	return object_as_type(obj, OBJ_COMMIT, quiet);
}

struct commit *lookup_commit_reference(const unsigned char *sha1)
{
	return lookup_commit_reference_gently(sha1, 0);
}
