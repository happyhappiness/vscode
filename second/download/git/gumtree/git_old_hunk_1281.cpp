		break;
	case GREP_PATTERN_TYPE_PCRE:
		argv_array_push(&submodule_options, "-P");
		break;
	case GREP_PATTERN_TYPE_UNSPECIFIED:
		break;
	}

	for (pattern = opt->pattern_list; pattern != NULL;
	     pattern = pattern->next) {
		switch (pattern->token) {
		case GREP_PATTERN:
