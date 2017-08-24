{
		n = 45 - shar->outpos;
		if (n > length)
			n = length;
		memcpy(shar->outbuff + shar->outpos, src, n);
		if (shar->outpos + n < 45) {
			shar->outpos += n;
			return length;
		}
		uuencode_line(a, shar, shar->outbuff, 45);
		src += n;
		n = length - n;
	}