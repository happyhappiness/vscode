static int add_submodule_odb(const char *path)
{
	struct strbuf objects_directory = STRBUF_INIT;
	struct alternate_object_database *alt_odb;
	int ret = 0;
	const char *git_dir;

	strbuf_addf(&objects_directory, "%s/.git", path);
	git_dir = read_gitfile(objects_directory.buf);
	if (git_dir) {
		strbuf_reset(&objects_directory);
		strbuf_addstr(&objects_directory, git_dir);
	}
	strbuf_addstr(&objects_directory, "/objects/");
	if (!is_directory(objects_directory.buf)) {
		ret = -1;
		goto done;
	}
	/* avoid adding it twice */
	for (alt_odb = alt_odb_list; alt_odb; alt_odb = alt_odb->next)
		if (alt_odb->name - alt_odb->base == objects_directory.len &&
				!strncmp(alt_odb->base, objects_directory.buf,
					objects_directory.len))
			goto done;

	alt_odb = xmalloc(objects_directory.len + 42 + sizeof(*alt_odb));
	alt_odb->next = alt_odb_list;
	strcpy(alt_odb->base, objects_directory.buf);
	alt_odb->name = alt_odb->base + objects_directory.len;
	alt_odb->name[2] = '/';
	alt_odb->name[40] = '\0';
	alt_odb->name[41] = '\0';
	alt_odb_list = alt_odb;

	/* add possible alternates from the submodule */
	read_info_alternates(objects_directory.buf, 0);
	prepare_alt_odb();
done:
	strbuf_release(&objects_directory);
	return ret;
}