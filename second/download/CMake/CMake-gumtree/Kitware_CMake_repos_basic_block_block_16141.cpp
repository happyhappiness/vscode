{
			int len;

			if (ptbl[i]->identifier == NULL)
				len = 1; /* root directory */
			else
				len = ptbl[i]->id_len;
			if (len & 0x01)
				len++; /* Padding Field */
			size += 8 + len;
		}