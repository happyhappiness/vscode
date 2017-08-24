{
			/* Ignore following unrecognized data. */
			state->eof = 1;
			*p = NULL;
			return (0);
		}