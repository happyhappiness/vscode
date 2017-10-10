
		assert(rr->items[i].util != RERERE_RESOLVED);

		id = rr->items[i].util;
		if (!id)
			continue;
		strbuf_addf(&buf, "%s\t%s%c",
			    rerere_id_hex(id),
			    rr->items[i].string, 0);
		if (write_in_full(out_fd, buf.buf, buf.len) != buf.len)
			die("unable to write rerere record");

		strbuf_release(&buf);
	}
	if (commit_lock_file(&write_lock) != 0)
