{
			/* Calculate next bit pattern */
			if ((bitptn[len] = ptn + cnt) > tbl_size)
				return (0);/* Invalid */
			/* Update the table */
			p = &(tbl[ptn]);
			while (--cnt >= 0)
				p[cnt] = (uint16_t)i;
			continue;
		}