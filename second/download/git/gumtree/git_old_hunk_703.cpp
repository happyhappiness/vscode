	struct strbuf sb = STRBUF_INIT;
	char *upd = NULL, *url = NULL, *displaypath;

	/* Only loads from .gitmodules, no overlay with .git/config */
	gitmodules_config();

	if (prefix) {
		strbuf_addf(&sb, "%s%s", prefix, path);
		displaypath = strbuf_detach(&sb, NULL);
	} else
		displaypath = xstrdup(path);

	sub = submodule_from_path(null_sha1, path);

