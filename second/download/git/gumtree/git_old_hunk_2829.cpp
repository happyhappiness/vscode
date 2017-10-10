}

static int grep_object(struct grep_opt *opt, const struct pathspec *pathspec,
		       struct object *obj, const char *name, const char *path)
{
	if (obj->type == OBJ_BLOB)
		return grep_sha1(opt, obj->sha1, name, 0, path);
	if (obj->type == OBJ_COMMIT || obj->type == OBJ_TREE) {
		struct tree_desc tree;
		void *data;
		unsigned long size;
		struct strbuf base;
		int hit, len;

		grep_read_lock();
		data = read_object_with_reference(obj->sha1, tree_type,
						  &size, NULL);
		grep_read_unlock();

		if (!data)
			die(_("unable to read tree (%s)"), sha1_to_hex(obj->sha1));

		len = name ? strlen(name) : 0;
		strbuf_init(&base, PATH_MAX + len + 1);
		if (len) {
			strbuf_add(&base, name, len);
			strbuf_addch(&base, ':');
