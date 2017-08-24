{
		const char *pb = p + len - nl;
		int name_len = 0;
		int slash;

		/* The form D accepts only a single line for an entry. */
		if (pb-2 >= p &&
		    pb[-1] == '\\' && (pb[-2] == ' ' || pb[-2] == '\t'))
			return (-1);
		if (pb-1 >= p && pb[-1] == '\\')
			return (-1);

		slash = 0;
		while (p <= --pb && *pb != ' ' && *pb != '\t') {
			if (!safe_char[*(const unsigned char *)pb])
				return (-1);
			name_len++;
			/* The pathname should have a slash in this
			 * format. */
			if (*pb == '/')
				slash = 1;
		}
		if (name_len == 0 || slash == 0)
			return (-1);
		/* If '/' is placed at the first in this field, this is not
		 * a valid filename. */
		if (pb[1] == '/')
			return (-1);
		ll = len - nl - name_len;
		pp = p;
		*last_is_path = 1;
	}