			ce_write(&c, newfd, sb.buf, sb.len) < 0;
		strbuf_release(&sb);
		if (err)
			return -1;
	}

	if (ce_flush(&c, newfd, istate->sha1))
		return -1;
	if (close_tempfile(tempfile))
		return error(_("could not close '%s'"), tempfile->filename.buf);
	if (stat(tempfile->filename.buf, &st))
		return -1;
	istate->timestamp.sec = (unsigned int)st.st_mtime;
	istate->timestamp.nsec = ST_MTIME_NSEC(st);
	return 0;
}

