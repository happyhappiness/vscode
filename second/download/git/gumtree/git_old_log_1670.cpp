warning("the merge base between %s and [%s] "
		"must be skipped.\n"
		"So we cannot be sure the first bad commit is "
		"between %s and %s.\n"
		"We continue anyway.",
		bad_hex, good_hex, mb_hex, bad_hex);