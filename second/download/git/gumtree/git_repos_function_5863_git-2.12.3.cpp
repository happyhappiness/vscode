static int grep_objects(struct grep_opt *opt, const struct pathspec *pathspec,
			const struct object_array *list)
{
	unsigned int i;
	int hit = 0;
	const unsigned int nr = list->nr;

	for (i = 0; i < nr; i++) {
		struct object *real_obj;
		real_obj = deref_tag(list->objects[i].item, NULL, 0);

		/* load the gitmodules file for this rev */
		if (recurse_submodules) {
			submodule_free();
			gitmodules_config_sha1(real_obj->oid.hash);
		}
		if (grep_object(opt, pathspec, real_obj, list->objects[i].name, list->objects[i].path)) {
			hit = 1;
			if (opt->status_only)
				break;
		}
	}
	return hit;
}