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
