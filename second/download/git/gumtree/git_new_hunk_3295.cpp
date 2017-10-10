			push_default = PUSH_DEFAULT_UPSTREAM;
		else if (!strcmp(value, "tracking")) /* deprecated */
			push_default = PUSH_DEFAULT_UPSTREAM;
		else if (!strcmp(value, "current"))
			push_default = PUSH_DEFAULT_CURRENT;
		else {
			error("malformed value for %s: %s", var, value);
			return error("Must be one of nothing, matching, simple, "
				     "upstream or current.");
		}
		return 0;
	}

