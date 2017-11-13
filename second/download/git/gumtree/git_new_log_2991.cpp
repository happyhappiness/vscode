error("%s: cannot verify a non-tag object of type %s.",
				name_to_report ?
				name_to_report :
				find_unique_abbrev(sha1, DEFAULT_ABBREV),
				typename(type));