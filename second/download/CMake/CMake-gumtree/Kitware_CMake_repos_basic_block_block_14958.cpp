(p = path; *p != '\0'; p++) {
		++alen;
		if (*p == '\\') {
			/* If previous byte is smaller than 128,
			 * this is not second byte of multibyte characters,
			 * so we can replace '\' with '/'. */
			if (utf8 || !mb)
				*p = '/';
			else
				complete = 0;/* uncompleted. */
		} else if (*(unsigned char *)p > 127)
			mb = 1;
		else
			mb = 0;
		/* Rewrite the path name if its next character is unusable. */
		if (*p == ':' || *p == '*' || *p == '?' || *p == '"' ||
		    *p == '<' || *p == '>' || *p == '|')
			*p = '_';
	}