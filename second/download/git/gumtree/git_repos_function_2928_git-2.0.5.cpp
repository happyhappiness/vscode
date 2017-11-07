static struct child_process *get_helper(struct transport *transport)
{
	struct helper_data *data = transport->data;
	struct argv_array argv = ARGV_ARRAY_INIT;
	struct strbuf buf = STRBUF_INIT;
	struct child_process *helper;
	const char **refspecs = NULL;
	int refspec_nr = 0;
	int refspec_alloc = 0;
	int duped;
	int code;
	char git_dir_buf[sizeof(GIT_DIR_ENVIRONMENT) + PATH_MAX + 1];
	const char *helper_env[] = {
		git_dir_buf,
		NULL
	};


	if (data->helper)
		return data->helper;

	helper = xcalloc(1, sizeof(*helper));
	helper->in = -1;
	helper->out = -1;
	helper->err = 0;
	argv_array_pushf(&argv, "git-remote-%s", data->name);
	argv_array_push(&argv, transport->remote->name);
	argv_array_push(&argv, remove_ext_force(transport->url));
	helper->argv = argv_array_detach(&argv, NULL);
	helper->git_cmd = 0;
	helper->silent_exec_failure = 1;

	snprintf(git_dir_buf, sizeof(git_dir_buf), "%s=%s", GIT_DIR_ENVIRONMENT, get_git_dir());
	helper->env = helper_env;

	code = start_command(helper);
	if (code < 0 && errno == ENOENT)
		die("Unable to find remote helper for '%s'", data->name);
	else if (code != 0)
		exit(code);

	data->helper = helper;
	data->no_disconnect_req = 0;

	/*
	 * Open the output as FILE* so strbuf_getline() can be used.
	 * Do this with duped fd because fclose() will close the fd,
	 * and stuff like taking over will require the fd to remain.
	 */
	duped = dup(helper->out);
	if (duped < 0)
		die_errno("Can't dup helper output fd");
	data->out = xfdopen(duped, "r");

	write_constant(helper->in, "capabilities\n");

	while (1) {
		const char *capname;
		int mandatory = 0;
		if (recvline(data, &buf))
			exit(128);

		if (!*buf.buf)
			break;

		if (*buf.buf == '*') {
			capname = buf.buf + 1;
			mandatory = 1;
		} else
			capname = buf.buf;

		if (debug)
			fprintf(stderr, "Debug: Got cap %s\n", capname);
		if (!strcmp(capname, "fetch"))
			data->fetch = 1;
		else if (!strcmp(capname, "option"))
			data->option = 1;
		else if (!strcmp(capname, "push"))
			data->push = 1;
		else if (!strcmp(capname, "import"))
			data->import = 1;
		else if (!strcmp(capname, "bidi-import"))
			data->bidi_import = 1;
		else if (!strcmp(capname, "export"))
			data->export = 1;
		else if (!strcmp(capname, "check-connectivity"))
			data->check_connectivity = 1;
		else if (!data->refspecs && starts_with(capname, "refspec ")) {
			ALLOC_GROW(refspecs,
				   refspec_nr + 1,
				   refspec_alloc);
			refspecs[refspec_nr++] = xstrdup(capname + strlen("refspec "));
		} else if (!strcmp(capname, "connect")) {
			data->connect = 1;
		} else if (!strcmp(capname, "signed-tags")) {
			data->signed_tags = 1;
		} else if (starts_with(capname, "export-marks ")) {
			data->export_marks = xstrdup(capname + strlen("export-marks "));
		} else if (starts_with(capname, "import-marks")) {
			data->import_marks = xstrdup(capname + strlen("import-marks "));
		} else if (starts_with(capname, "no-private-update")) {
			data->no_private_update = 1;
		} else if (mandatory) {
			die("Unknown mandatory capability %s. This remote "
			    "helper probably needs newer version of Git.",
			    capname);
		}
	}
	if (refspecs) {
		int i;
		data->refspec_nr = refspec_nr;
		data->refspecs = parse_fetch_refspec(refspec_nr, refspecs);
		for (i = 0; i < refspec_nr; i++)
			free((char *)refspecs[i]);
		free(refspecs);
	} else if (data->import || data->bidi_import || data->export) {
		warning("This remote helper should implement refspec capability.");
	}
	strbuf_release(&buf);
	if (debug)
		fprintf(stderr, "Debug: Capabilities complete.\n");
	return data->helper;
}