static int parse_one_feature(const char *feature, int from_stream)
{
	if (starts_with(feature, "date-format=")) {
		option_date_format(feature + 12);
	} else if (starts_with(feature, "import-marks=")) {
		option_import_marks(feature + 13, from_stream, 0);
	} else if (starts_with(feature, "import-marks-if-exists=")) {
		option_import_marks(feature + strlen("import-marks-if-exists="),
					from_stream, 1);
	} else if (starts_with(feature, "export-marks=")) {
		option_export_marks(feature + 13);
	} else if (!strcmp(feature, "cat-blob")) {
		; /* Don't die - this feature is supported */
	} else if (!strcmp(feature, "relative-marks")) {
		relative_marks_paths = 1;
	} else if (!strcmp(feature, "no-relative-marks")) {
		relative_marks_paths = 0;
	} else if (!strcmp(feature, "done")) {
		require_explicit_termination = 1;
	} else if (!strcmp(feature, "force")) {
		force_update = 1;
	} else if (!strcmp(feature, "notes") || !strcmp(feature, "ls")) {
		; /* do nothing; we have the feature */
	} else {
		return 0;
	}

	return 1;
}