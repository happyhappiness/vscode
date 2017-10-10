	else if (dash_dash_pos >= 2)
		die(_("only one reference expected, %d given."), dash_dash_pos);

	if (!strcmp(arg, "-"))
		arg = "@{-1}";

	if (get_sha1_mb(arg, rev)) {
		/*
		 * Either case (3) or (4), with <something> not being
		 * a commit, or an attempt to use case (1) with an
		 * invalid ref.
		 *
		 * It's likely an error, but we need to find out if
