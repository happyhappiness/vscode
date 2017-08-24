(r == 0)
			aes->aes_set |= AES_SET_MBS;
		else if (errno == ENOMEM)
			return (-1);
		else
			ret = -1