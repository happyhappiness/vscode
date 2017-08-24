(r == 0) {
			aes->aes_set |= AES_SET_UTF8;
			*p = aes->aes_utf8.s;
			return (0);/* success. */
		} else
			return (-1);