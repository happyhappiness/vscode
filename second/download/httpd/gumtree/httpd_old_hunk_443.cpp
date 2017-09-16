	}



	/* Compress the line, reducing all blanks and tabs to one space.

	 * Leading and trailing white space is eliminated completely

	 */

	src = dst = buf;

	while (isspace(*src))

	    ++src;

	while (*src != '\0')

	{

	    /* Copy words */

	    while (!isspace(*dst = *src) && *src != '\0') {

		++src;

		++dst;

	    }

	    if (*src == '\0') break;

	    *dst++ = ' ';

	    while (isspace(*src))

		++src;

	}

	*dst = '\0';

	/* blast trailing whitespace */

	while (--dst >= buf && isspace(*dst))

	    *dst = '\0';



#ifdef DEBUG_CFG_LINES

	ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, NULL, "Read config: %s", buf);

#endif

	return 0;

