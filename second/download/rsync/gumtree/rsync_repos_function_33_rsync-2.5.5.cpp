static struct exclude_struct *make_exclude(const char *pattern, int include)
{
	struct exclude_struct *ret;

	ret = (struct exclude_struct *)malloc(sizeof(*ret));
	if (!ret) out_of_memory("make_exclude");

	memset(ret, 0, sizeof(*ret));

	if (strncmp(pattern,"- ",2) == 0) {
		pattern += 2;
	} else if (strncmp(pattern,"+ ",2) == 0) {
		ret->include = 1;
		pattern += 2;
	} else {
		ret->include = include;
	}

	ret->pattern = strdup(pattern);

	if (!ret->pattern) out_of_memory("make_exclude");

	if (strpbrk(pattern, "*[?")) {
	    ret->regular_exp = 1;
	    ret->fnmatch_flags = FNM_PATHNAME;
	    if (strstr(pattern, "**")) {
		    static int tested;
		    if (!tested) {
			    tested = 1;
			    if (fnmatch("a/b/*", "a/b/c/d", FNM_PATHNAME)==0) {
				    rprintf(FERROR,"WARNING: fnmatch FNM_PATHNAME is broken on your system\n");
			    }
		    }
		    ret->fnmatch_flags = 0;
	    }
	}

	if (strlen(pattern) > 1 && pattern[strlen(pattern)-1] == '/') {
		ret->pattern[strlen(pattern)-1] = 0;
		ret->directory = 1;
	}

	if (!strchr(ret->pattern,'/')) {
		ret->local = 1;
	}

	return ret;
}