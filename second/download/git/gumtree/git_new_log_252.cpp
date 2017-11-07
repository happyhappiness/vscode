warning(Q_("cannot handle more than %d base. "
				   "Ignoring %s.",
				   "cannot handle more than %d bases. "
				   "Ignoring %s.",
				    (int)ARRAY_SIZE(bases)-1),
				(int)ARRAY_SIZE(bases)-1, argv[i]);