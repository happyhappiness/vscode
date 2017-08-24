{
			length += 1; /* colon */
			/* ID digit count */
			idlen = 1;
			tmp = ap->id;
			while (tmp > 9) {
				tmp = tmp / 10;
				idlen++;
			}
			length += idlen;
		}