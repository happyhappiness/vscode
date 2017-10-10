 	git_inflate_init(&stream);
 	stream.next_out = data;
 	stream.avail_out = consume ? 64*1024 : obj->size;
 
 	do {
 		ssize_t n = (len < 64*1024) ? len : 64*1024;
-		n = pread(pack_fd, inbuf, n, from);
+		n = xpread(get_thread_data()->pack_fd, inbuf, n, from);
 		if (n < 0)
 			die_errno(_("cannot pread pack file"));
 		if (!n)
 			die(Q_("premature end of pack file, %lu byte missing",
 			       "premature end of pack file, %lu bytes missing",
 			       len),
