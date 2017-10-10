		if (!keep_cr && buf.len > 1 && buf.buf[buf.len-1] == '\n' &&
			buf.buf[buf.len-2] == '\r') {
			strbuf_setlen(&buf, buf.len-2);
			strbuf_addch(&buf, '\n');
		}

		if (fwrite(buf.buf, 1, buf.len, output) != buf.len)
			die_errno("cannot write output");

		if (strbuf_getwholeline(&buf, mbox, '\n')) {
			if (feof(mbox)) {
				status = 1;
