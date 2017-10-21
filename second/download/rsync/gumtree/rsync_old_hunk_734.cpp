	}
	while (*p != '\0') {
		/* this loop iterates once per filename component in p.
		 * both p (and sanp if the original had a slash) should
		 * always be left pointing after a slash
		 */
		if ((*p == '.') && ((*(p+1) == '/') || (*(p+1) == '\0'))) {
			/* skip "." component */
			while (*++p == '/') {
				/* skip following slashes */
				;
			}
			continue;
		}
		allowdotdot = 0;
		if ((*p == '.') && (*(p+1) == '.') &&
		    ((*(p+2) == '/') || (*(p+2) == '\0'))) {
			/* ".." component followed by slash or end */
			if ((depth > 0) && (sanp == start)) {
				/* allow depth levels of .. at the beginning */
				--depth;
				allowdotdot = 1;
			} else {
				p += 2;
				if (*p == '/')
					p++;
				if (sanp != start) {
					/* back up sanp one level */
					--sanp; /* now pointing at slash */
					while ((sanp > start) && (*(sanp - 1) != '/')) {
						/* skip back up to slash */
						sanp--;
					}
				}
				continue;
			}
		}
		while (1) {
			/* copy one component through next slash */
			*sanp++ = *p++;
			if ((*p == '\0') || (*(p-1) == '/')) {
				while (*p == '/') {
					/* skip multiple slashes */
					p++;
				}
				break;
			}
		}
		if (allowdotdot) {
			/* move the virtual beginning to leave the .. alone */
			start = sanp;
		}
	}
	if ((sanp == start) && !allowdotdot) {
		/* ended up with nothing, so put in "." component */
		/*
		 * note that the !allowdotdot doesn't prevent this from
		 *  happening in all allowed ".." situations, but I didn't
		 *  think it was worth putting in an extra variable to ensure
		 *  it since an extra "." won't hurt in those situations.
		 */
		*sanp++ = '.';
	}
	*sanp = '\0';
}


char curr_dir[MAXPATHLEN];

/**
 * Like chdir() but can be reversed with pop_dir() if @p save is set.
 * It is also much faster as it remembers where we have been.
 **/
char *push_dir(char *dir, int save)
{
	char *ret = curr_dir;
	static int initialised;

	if (!initialised) {
		initialised = 1;
		getcwd(curr_dir, sizeof(curr_dir)-1);
	}

	if (!dir) return NULL; /* this call was probably just to initialize */

	if (chdir(dir)) return NULL;

	if (save) {
		ret = strdup(curr_dir);
	}

	if (*dir == '/') {
		strlcpy(curr_dir, dir, sizeof(curr_dir));
	} else if (dir[0] != '.' || dir[1] != '\0') {
		strlcat(curr_dir,"/", sizeof(curr_dir));
		strlcat(curr_dir,dir, sizeof(curr_dir));
	}

	clean_fname(curr_dir);

	return ret;
}

/** Reverse a push_dir() call */
int pop_dir(char *dir)
{
	int ret;

	ret = chdir(dir);
	if (ret) {
		free(dir);
		return ret;
	}

	strlcpy(curr_dir, dir, sizeof(curr_dir));

	free(dir);

	return 0;
}

/**
 * Return a quoted string with the full pathname of the indicated filename.
 * The string " (in MODNAME)" may also be appended.  The returned pointer
 * remains valid until the next time full_fname() is called.
