{
		struct isoent **ptbl;
		int i, cnt;

		if ((cnt = pt[depth].cnt) == 0)
			break;

		ptbl = pt[depth].sorted;
		for (i = 0; i < cnt; i++) {
			int len;

			if (ptbl[i]->identifier == NULL)
				len = 1; /* root directory */
			else
				len = ptbl[i]->id_len;
			if (len & 0x01)
				len++; /* Padding Field */
			size += 8 + len;
		}
	}