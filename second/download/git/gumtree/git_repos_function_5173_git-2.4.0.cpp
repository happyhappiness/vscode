static int add(int argc, const char **argv)
{
	int fetch = 0, fetch_tags = TAGS_DEFAULT;
	unsigned mirror = MIRROR_NONE;
	struct string_list track = STRING_LIST_INIT_NODUP;
	const char *master = NULL;
	struct remote *remote;
	struct strbuf buf = STRBUF_INIT, buf2 = STRBUF_INIT;
	const char *name, *url;
	int i;

	struct option options[] = {
		OPT_BOOL('f', "fetch", &fetch, N_("fetch the remote branches")),
		OPT_SET_INT(0, "tags", &fetch_tags,
			    N_("import all tags and associated objects when fetching"),
			    TAGS_SET),
		OPT_SET_INT(0, NULL, &fetch_tags,
			    N_("or do not fetch any tag at all (--no-tags)"), TAGS_UNSET),
		OPT_STRING_LIST('t', "track", &track, N_("branch"),
				N_("branch(es) to track")),
		OPT_STRING('m', "master", &master, N_("branch"), N_("master branch")),
		{ OPTION_CALLBACK, 0, "mirror", &mirror, N_("push|fetch"),
			N_("set up remote as a mirror to push to or fetch from"),
			PARSE_OPT_OPTARG, parse_mirror_opt },
		OPT_END()
	};

	argc = parse_options(argc, argv, NULL, options, builtin_remote_add_usage,
			     0);

	if (argc != 2)
		usage_with_options(builtin_remote_add_usage, options);

	if (mirror && master)
		die(_("specifying a master branch makes no sense with --mirror"));
	if (mirror && !(mirror & MIRROR_FETCH) && track.nr)
		die(_("specifying branches to track makes sense only with fetch mirrors"));

	name = argv[0];
	url = argv[1];

	remote = remote_get(name);
	if (remote && (remote->url_nr > 1 ||
			(strcmp(name, remote->url[0]) &&
				strcmp(url, remote->url[0])) ||
			remote->fetch_refspec_nr))
		die(_("remote %s already exists."), name);

	strbuf_addf(&buf2, "refs/heads/test:refs/remotes/%s/test", name);
	if (!valid_fetch_refspec(buf2.buf))
		die(_("'%s' is not a valid remote name"), name);

	strbuf_addf(&buf, "remote.%s.url", name);
	if (git_config_set(buf.buf, url))
		return 1;

	if (!mirror || mirror & MIRROR_FETCH) {
		strbuf_reset(&buf);
		strbuf_addf(&buf, "remote.%s.fetch", name);
		if (track.nr == 0)
			string_list_append(&track, "*");
		for (i = 0; i < track.nr; i++) {
			if (add_branch(buf.buf, track.items[i].string,
				       name, mirror, &buf2))
				return 1;
		}
	}

	if (mirror & MIRROR_PUSH) {
		strbuf_reset(&buf);
		strbuf_addf(&buf, "remote.%s.mirror", name);
		if (git_config_set(buf.buf, "true"))
			return 1;
	}

	if (fetch_tags != TAGS_DEFAULT) {
		strbuf_reset(&buf);
		strbuf_addf(&buf, "remote.%s.tagopt", name);
		if (git_config_set(buf.buf,
			fetch_tags == TAGS_SET ? "--tags" : "--no-tags"))
			return 1;
	}

	if (fetch && fetch_remote(name))
		return 1;

	if (master) {
		strbuf_reset(&buf);
		strbuf_addf(&buf, "refs/remotes/%s/HEAD", name);

		strbuf_reset(&buf2);
		strbuf_addf(&buf2, "refs/remotes/%s/%s", name, master);

		if (create_symref(buf.buf, buf2.buf, "remote add"))
			return error(_("Could not setup master '%s'"), master);
	}

	strbuf_release(&buf);
	strbuf_release(&buf2);
	string_list_clear(&track, 0);

	return 0;
}