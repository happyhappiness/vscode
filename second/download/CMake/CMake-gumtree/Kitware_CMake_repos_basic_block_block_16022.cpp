{
				/*
				 * This action is similar to mkisofs -r option
				 * but our rockridge=useful option does not
				 * set a zero to uid and gid.
				 */
				/* set all read bit ON */
				mode |= 0444;
#if !defined(_WIN32) && !defined(__CYGWIN__)
				if (mode & 0111)
#endif
					/* set all exec bit ON */
					mode |= 0111;
				/* clear all write bits. */
				mode &= ~0222;
				/* clear setuid,setgid,sticky bits. */
				mode &= ~07000;
			}