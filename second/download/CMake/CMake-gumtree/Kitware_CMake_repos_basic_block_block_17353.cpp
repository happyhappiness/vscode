{
		/*
		 * Get the path of a shell script if so.
		 */
		const unsigned char *b = (const unsigned char *)buff;

		archive_string_empty(&(xar->cur_file->script));
		if (rsize > 2 && b[0] == '#' && b[1] == '!') {
			size_t i, end, off;

			off = 2;
			if (b[off] == ' ')
				off++;
#ifdef PATH_MAX
			if ((rsize - off) > PATH_MAX)
				end = off + PATH_MAX;
			else
#endif
				end = rsize;
			/* Find the end of a script path. */
			for (i = off; i < end && b[i] != '\0' &&
			    b[i] != '\n' && b[i] != '\r' &&
			    b[i] != ' ' && b[i] != '\t'; i++)
				;
			archive_strncpy(&(xar->cur_file->script), b + off,
			    i - off);
		}
	}