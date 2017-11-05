static void handle_bad_merge_base(void)
{
	if (is_expected_rev(current_bad_oid)) {
		char *bad_hex = oid_to_hex(current_bad_oid);
		char *good_hex = join_sha1_array_hex(&good_revs, ' ');
		if (!strcmp(term_bad, "bad") && !strcmp(term_good, "good")) {
			fprintf(stderr, _("The merge base %s is bad.\n"
				"This means the bug has been fixed "
				"between %s and [%s].\n"),
				bad_hex, bad_hex, good_hex);
		} else if (!strcmp(term_bad, "new") && !strcmp(term_good, "old")) {
			fprintf(stderr, _("The merge base %s is new.\n"
				"The property has changed "
				"between %s and [%s].\n"),
				bad_hex, bad_hex, good_hex);
		} else {
			fprintf(stderr, _("The merge base %s is %s.\n"
				"This means the first '%s' commit is "
				"between %s and [%s].\n"),
				bad_hex, term_bad, term_good, bad_hex, good_hex);
		}
		exit(3);
	}

	fprintf(stderr, _("Some %s revs are not ancestor of the %s rev.\n"
		"git bisect cannot work properly in this case.\n"
		"Maybe you mistook %s and %s revs?\n"),
		term_good, term_bad, term_good, term_bad);
	exit(1);
}