{
		char tmp_buf[3];
		tmp_buf[0] = inbuf[0];
		if (len == 1)
			tmp_buf[1] = '\0';
		else
			tmp_buf[1] = inbuf[1];
		tmp_buf[2] = '\0';
		uuencode_group(tmp_buf, buf);
		buf += 4;
	}