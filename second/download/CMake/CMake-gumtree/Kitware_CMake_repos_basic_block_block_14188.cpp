(r == 0) {
			*p = aes->aes_mbs_in_locale.s;
			if (length != NULL)
				*length = aes->aes_mbs_in_locale.length;
			return (0);
		} else if (errno == ENOMEM)
			return (-1);
		else
			ret = -1