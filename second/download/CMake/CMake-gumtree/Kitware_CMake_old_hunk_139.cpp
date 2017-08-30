		r = archive_match_path_excluded(a->matching, entry);

		if (r < 0) {

			archive_set_error(&(a->archive), errno,

			    "Faild : %s", archive_error_string(a->matching));

			return (r);

		}

		if (r) {

