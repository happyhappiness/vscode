		else if (!strcmp(capname, "bidi-import"))
			data->bidi_import = 1;
		else if (!strcmp(capname, "export"))
			data->export = 1;
		else if (!strcmp(capname, "check-connectivity"))
			data->check_connectivity = 1;
		else if (!data->refspecs && skip_prefix(capname, "refspec ", &arg)) {
			ALLOC_GROW(refspecs,
				   refspec_nr + 1,
				   refspec_alloc);
			refspecs[refspec_nr++] = xstrdup(arg);
		} else if (!strcmp(capname, "connect")) {
			data->connect = 1;
		} else if (!strcmp(capname, "signed-tags")) {
			data->signed_tags = 1;
		} else if (skip_prefix(capname, "export-marks ", &arg)) {
			data->export_marks = xstrdup(arg);
		} else if (skip_prefix(capname, "import-marks ", &arg)) {
			data->import_marks = xstrdup(arg);
		} else if (starts_with(capname, "no-private-update")) {
			data->no_private_update = 1;
		} else if (mandatory) {
			die("Unknown mandatory capability %s. This remote "
			    "helper probably needs newer version of Git.",
			    capname);
