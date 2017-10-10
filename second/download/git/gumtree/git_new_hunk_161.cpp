			fprintf(o->file, "%sBinary files %s and %s differ\n",
				line_prefix, lbl[0], lbl[1]);
		o->found_changes = 1;
	} else {
		/* Crazy xdl interfaces.. */
		const char *diffopts = getenv("GIT_DIFF_OPTS");
		const char *v;
		xpparam_t xpp;
		xdemitconf_t xecfg;
		struct emit_callback ecbdata;
		const struct userdiff_funcname *pe;

		if (must_show_header) {
