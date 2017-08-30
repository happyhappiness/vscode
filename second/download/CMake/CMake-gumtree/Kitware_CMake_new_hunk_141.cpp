		r = archive_match_owner_excluded(a->matching, entry);

		if (r < 0) {

			archive_set_error(&(a->archive), errno,

			    "Failed : %s", archive_error_string(a->matching));

			return (r);

		}

		if (r) {

