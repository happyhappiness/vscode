void sanitize_path(char *p, char *reldir)
{
	char *start, *sanp;
	int depth = 0;
	int allowdotdot = 0;

	if (reldir) {
		depth++;
		while (*reldir) {
			if (*reldir++ == '/') {
				depth++;
			}
		}
	}
	start = p;
	sanp = p;
	while (*p == '/') {
		/* remove leading slashes */
		p++;
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