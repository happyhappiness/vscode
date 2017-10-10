				"between %s and [%s].\n"),
				bad_hex, term_bad, term_good, bad_hex, good_hex);
		}
		exit(3);
	}

	fprintf(stderr, _("Some %s revs are not ancestors of the %s rev.\n"
		"git bisect cannot work properly in this case.\n"
		"Maybe you mistook %s and %s revs?\n"),
		term_good, term_bad, term_good, term_bad);
	exit(1);
}

