static int mv(int argc, const char **argv)
{
	struct option options[] = {
		OPT_END()
	};
	struct remote *oldremote, *newremote;
	struct strbuf buf = STRBUF_INIT, buf2 = STRBUF_INIT, buf3 = STRBUF_INIT,
		old_remote_context = STRBUF_INIT;
	struct string_list remote_branches = STRING_LIST_INIT_NODUP;
	struct rename_info rename;
	int i, refspec_updated = 0;

	if (argc != 3)
		usage_with_options(builtin_remote_rename_usage, options);

	rename.old = argv[1];
	rename.new = argv[2];
	rename.remote_branches = &remote_branches;

	oldremote = remote_get(rename.old);
	if (!oldremote)
		die(_("No such remote: %s"), rename.old);

	if (!strcmp(rename.old, rename.new) && oldremote->origin != REMOTE_CONFIG)
		return migrate_file(oldremote);

	newremote = remote_get(rename.new);
	if (newremote && (newremote->url_nr > 1 || newremote->fetch_refspec_nr))
		die(_("remote %s already exists."), rename.new);

	strbuf_addf(&buf, "refs/heads/test:refs/remotes/%s/test", rename.new);
	if (!valid_fetch_refspec(buf.buf))
		die(_("'%s' is not a valid remote name"), rename.new);

	strbuf_reset(&buf);
	strbuf_addf(&buf, "remote.%s", rename.old);
	strbuf_addf(&buf2, "remote.%s", rename.new);
	if (git_config_rename_section(buf.buf, buf2.buf) < 1)
		return error(_("Could not rename config section '%s' to '%s'"),
				buf.buf, buf2.buf);

	strbuf_reset(&buf);
	strbuf_addf(&buf, "remote.%s.fetch", rename.new);
	if (git_config_set_multivar(buf.buf, NULL, NULL, 1))
		return error(_("Could not remove config section '%s'"), buf.buf);
	strbuf_addf(&old_remote_context, ":refs/remotes/%s/", rename.old);
	for (i = 0; i < oldremote->fetch_refspec_nr; i++) {
		char *ptr;

		strbuf_reset(&buf2);
		strbuf_addstr(&buf2, oldremote->fetch_refspec[i]);
		ptr = strstr(buf2.buf, old_remote_context.buf);
		if (ptr) {
			refspec_updated = 1;
			strbuf_splice(&buf2,
				      ptr-buf2.buf + strlen(":refs/remotes/"),
				      strlen(rename.old), rename.new,
				      strlen(rename.new));
		} else
			warning(_("Not updating non-default fetch refspec\n"
				  "\t%s\n"
				  "\tPlease update the configuration manually if necessary."),
				buf2.buf);

		if (git_config_set_multivar(buf.buf, buf2.buf, "^$", 0))
			return error(_("Could not append '%s'"), buf.buf);
	}

	read_branches();
	for (i = 0; i < branch_list.nr; i++) {
		struct string_list_item *item = branch_list.items + i;
		struct branch_info *info = item->util;
		if (info->remote_name && !strcmp(info->remote_name, rename.old)) {
			strbuf_reset(&buf);
			strbuf_addf(&buf, "branch.%s.remote", item->string);
			if (git_config_set(buf.buf, rename.new)) {
				return error(_("Could not set '%s'"), buf.buf);
			}
		}
	}

	if (!refspec_updated)
		return 0;

	/*
	 * First remove symrefs, then rename the rest, finally create
	 * the new symrefs.
	 */
	for_each_ref(read_remote_branches, &rename);
	for (i = 0; i < remote_branches.nr; i++) {
		struct string_list_item *item = remote_branches.items + i;
		int flag = 0;
		struct object_id oid;

		read_ref_full(item->string, RESOLVE_REF_READING, oid.hash, &flag);
		if (!(flag & REF_ISSYMREF))
			continue;
		if (delete_ref(item->string, NULL, REF_NODEREF))
			die(_("deleting '%s' failed"), item->string);
	}
	for (i = 0; i < remote_branches.nr; i++) {
		struct string_list_item *item = remote_branches.items + i;

		if (item->util)
			continue;
		strbuf_reset(&buf);
		strbuf_addstr(&buf, item->string);
		strbuf_splice(&buf, strlen("refs/remotes/"), strlen(rename.old),
				rename.new, strlen(rename.new));
		strbuf_reset(&buf2);
		strbuf_addf(&buf2, "remote: renamed %s to %s",
				item->string, buf.buf);
		if (rename_ref(item->string, buf.buf, buf2.buf))
			die(_("renaming '%s' failed"), item->string);
	}
	for (i = 0; i < remote_branches.nr; i++) {
		struct string_list_item *item = remote_branches.items + i;

		if (!item->util)
			continue;
		strbuf_reset(&buf);
		strbuf_addstr(&buf, item->string);
		strbuf_splice(&buf, strlen("refs/remotes/"), strlen(rename.old),
				rename.new, strlen(rename.new));
		strbuf_reset(&buf2);
		strbuf_addstr(&buf2, item->util);
		strbuf_splice(&buf2, strlen("refs/remotes/"), strlen(rename.old),
				rename.new, strlen(rename.new));
		strbuf_reset(&buf3);
		strbuf_addf(&buf3, "remote: renamed %s to %s",
				item->string, buf.buf);
		if (create_symref(buf.buf, buf2.buf, buf3.buf))
			die(_("creating '%s' failed"), buf.buf);
	}
	return 0;
}