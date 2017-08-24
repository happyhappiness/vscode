{
			/* Conversion is unneeded. */
			*p = aes->aes_mbs.s;
			if (length != NULL)
				*length = aes->aes_mbs.length;
			return (0);
		}