		char *good_hex = join_sha1_array_hex(&good_revs, ' ');
		if (!strcmp(term_bad, "bad") && !strcmp(term_good, "good")) {
			fprintf(stderr, "The merge base %s is bad.\n"
				"This means the bug has been fixed "
				"between %s and [%s].\n",
				bad_hex, bad_hex, good_hex);
		} else {
			fprintf(stderr, "The merge base %s is %s.\n"
				"This means the first '%s' commit is "
				"between %s and [%s].\n",
				bad_hex, term_bad, term_good, bad_hex, good_hex);
		}
