		die_errno("Unable to create temporary file '%s'",
			nonrelative_template);
	}
	return fd;
}

/* Adapted from libiberty's mkstemp.c. */

#undef TMP_MAX
#define TMP_MAX 16384

int git_mkstemps_mode(char *pattern, int suffix_len, int mode)
