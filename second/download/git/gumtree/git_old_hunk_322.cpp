		if (errno == ENOENT)
			return;
		die("cannot open '%s' for reading", git_path_merge_head());
	}

	while (!strbuf_getwholeline_fd(&line, merge_head, '\n')) {
		unsigned char sha1[20];
		if (line.len < 40 || get_sha1_hex(line.buf, sha1))
			die("unknown line in '%s': %s", git_path_merge_head(), line.buf);
		tail = append_parent(tail, sha1);
	}
	close(merge_head);
	strbuf_release(&line);
}

/*
