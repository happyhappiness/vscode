{
		len = bid_get_line(filter, &b, &avail, &ravail, &nl, &nbytes_read);
		if (len < 0 || nl == 0)
			return (0); /* No match found. */
		if (len - nl >= 11 && memcmp(b, "begin ", 6) == 0)
			l = 6;
		else if (len -nl >= 18 && memcmp(b, "begin-base64 ", 13) == 0)
			l = 13;
		else
			l = 0;

		if (l > 0 && (b[l] < '0' || b[l] > '7' ||
		    b[l+1] < '0' || b[l+1] > '7' ||
		    b[l+2] < '0' || b[l+2] > '7' || b[l+3] != ' '))
			l = 0;

		b += len;
		avail -= len;
		if (l)
			break;
		firstline = 0;

		/* Do not read more than UUENCODE_BID_MAX_READ bytes */
		if (nbytes_read >= UUENCODE_BID_MAX_READ)
			return (0);
	}