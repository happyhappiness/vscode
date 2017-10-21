
	ret->pattern = strdup(pattern);

	if (!ret->pattern) out_of_memory("make_exclude");

	if (strpbrk(pattern, "*[?")) {
	    if (!ret->include && (*pattern == '*') && (*(pattern+1) == '\0')) {
		    exclude_the_rest = ret;
	    } else {
		    only_included_files = 0;
	    }
	    ret->regular_exp = 1;
	    ret->fnmatch_flags = strstr(pattern, "**") ? 0 : FNM_PATHNAME;
	} else if (!ret->include) {
		only_included_files = 0;
	}

	if (strlen(pattern) > 1 && pattern[strlen(pattern)-1] == '/') {
		ret->pattern[strlen(pattern)-1] = 0;
		ret->directory = 1;
	}
