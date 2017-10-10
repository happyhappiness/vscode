 	}
 	argv[argc++] = url.buf;
 	argv[argc++] = NULL;
 
 	for (i = 0; i < nr_heads; i++) {
 		struct ref *ref = to_fetch[i];
-		if (!ref->name || !*ref->name)
+		if (!*ref->name)
 			die("cannot fetch by sha1 over smart http");
 		packet_buf_write(&preamble, "%s %s\n",
 				 sha1_to_hex(ref->old_sha1), ref->name);
 	}
 	packet_buf_flush(&preamble);
 
