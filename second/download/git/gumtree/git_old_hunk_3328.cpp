	if (!fp) {
		if (errno == ENOENT) {
			*read_bad = "bad";
			*read_good = "good";
			return;
		} else {
			die("could not read file '%s': %s", filename,
				strerror(errno));
		}
	} else {
		strbuf_getline_lf(&str, fp);
		*read_bad = strbuf_detach(&str, NULL);
		strbuf_getline_lf(&str, fp);
		*read_good = strbuf_detach(&str, NULL);
