 			sha1close(f, sha1, CSUM_FSYNC);
 		} else {
 			int fd = sha1close(f, sha1, 0);
 			fixup_pack_header_footer(fd, sha1, pack_tmp_name,
 						 nr_written, sha1, offset);
 			close(fd);
-			write_bitmap_index = 0;
+			if (write_bitmap_index) {
+				warning(_(no_split_warning));
+				write_bitmap_index = 0;
+			}
 		}
 
 		if (!pack_to_stdout) {
 			struct stat st;
 			struct strbuf tmpname = STRBUF_INIT;
 
