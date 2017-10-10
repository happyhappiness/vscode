
	if (!editor)
		return error("Terminal is dumb, but EDITOR unset");

	if (strcmp(editor, ":")) {
		const char *args[] = { editor, real_path(path), NULL };
		struct child_process p;
		int ret, sig;

		memset(&p, 0, sizeof(p));
		p.argv = args;
		p.env = env;
		p.use_shell = 1;
		if (start_command(&p) < 0)
			return error("unable to start editor '%s'", editor);

