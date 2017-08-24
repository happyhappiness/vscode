{
			/* If we have not met any multi-byte characters,
			 * we can replace '\' with '/'. */
			if (!mb)
				*p = '/';
			dos = 1;
		}