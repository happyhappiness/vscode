{
			result = &pwent; /* Old getpwnam_r ignores last arg. */
			r = getpwnam_r(uname, &pwent, buffer, bufsize, &result);
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