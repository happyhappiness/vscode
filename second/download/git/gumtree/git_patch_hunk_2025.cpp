 
 		for (;;) {
 			readlen = read_istream(stream, buf, sizeof(buf));
 			if (readlen <= 0)
 				break;
 			crc = crc32(crc, buf, readlen);
+			if (is_binary == -1)
+				is_binary = entry_is_binary(path_without_prefix,
+							    buf, readlen);
 
 			zstream.next_in = buf;
 			zstream.avail_in = readlen;
 			result = git_deflate(&zstream, 0);
 			if (result != Z_OK)
 				die("deflate error (%d)", result);
