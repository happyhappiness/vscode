fprintf(stderr, "Some %s revs are not ancestor of the %s rev.\n"
		"git bisect cannot work properly in this case.\n"
		"Maybe you mistook %s and %s revs?\n",
		term_good, term_bad, term_good, term_bad);