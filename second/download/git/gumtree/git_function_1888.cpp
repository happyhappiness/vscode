static int mark_object(struct object *obj, int type, void *data, struct fsck_options *options)
{
	struct object *parent = data;

	/*
	 * The only case data is NULL or type is OBJ_ANY is when
	 * mark_object_reachable() calls us.  All the callers of
	 * that function has non-NULL obj hence ...
	 */
	if (!obj) {
		/* ... these references to parent->fld are safe here */
		printf("broken link from %7s %s\n",
			   typename(parent->type), sha1_to_hex(parent->sha1));
		printf("broken link from %7s %s\n",
			   (type == OBJ_ANY ? "unknown" : typename(type)), "unknown");
		errors_found |= ERROR_REACHABLE;
		return 1;
	}

	if (type != OBJ_ANY && obj->type != type)
		/* ... and the reference to parent is safe here */
		objerror(parent, "wrong object type in link");

	if (obj->flags & REACHABLE)
		return 0;
	obj->flags |= REACHABLE;
	if (!(obj->flags & HAS_OBJ)) {
		if (parent && !has_sha1_file(obj->sha1)) {
			printf("broken link from %7s %s\n",
				 typename(parent->type), sha1_to_hex(parent->sha1));
			printf("              to %7s %s\n",
				 typename(obj->type), sha1_to_hex(obj->sha1));
			errors_found |= ERROR_REACHABLE;
		}
		return 1;
	}

	add_object_array(obj, NULL, &pending);
	return 0;
}