{
			result = &grent; /* Old getgrnam_r ignores last arg. */
			r = getgrnam_r(gname, &grent, buffer, bufsize, &result);
			if (r == 0)
				break;
			if (r != ERANGE)
				break;
			bufsize *= 2;
			free(allocated);
			allocated = malloc(bufsize);
			if (allocated == NULL)
				break;
			buffer = allocated;
		}