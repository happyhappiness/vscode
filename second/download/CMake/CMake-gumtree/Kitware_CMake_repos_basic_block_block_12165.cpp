{
			if (!safe_char[*(const unsigned char *)pb])
				return (-1);
			name_len++;
			/* The pathname should have a slash in this
			 * format. */
			if (*pb == '/')
				slash = 1;
		}