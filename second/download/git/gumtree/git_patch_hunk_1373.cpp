 		int ret = git_inflate(&stream, 0);
 		use(len - stream.avail_in);
 		if (stream.total_out == size && ret == Z_STREAM_END)
 			break;
 		if (ret != Z_OK) {
 			error("inflate returned %d", ret);
-			free(buf);
-			buf = NULL;
+			FREE_AND_NULL(buf);
 			if (!recover)
 				exit(1);
 			has_errors = 1;
 			break;
 		}
 		stream.next_in = fill(1);
