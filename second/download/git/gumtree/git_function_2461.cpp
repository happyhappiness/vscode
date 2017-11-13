int fsck_error_function(struct object *obj, int msg_type, const char *message)
{
	if (msg_type == FSCK_WARN) {
		warning("object %s: %s", sha1_to_hex(obj->sha1), message);
		return 0;
	}
	error("object %s: %s", sha1_to_hex(obj->sha1), message);
	return 1;
}