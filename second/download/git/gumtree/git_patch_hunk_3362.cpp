 			 * order since newer packs are more likely to contain
 			 * younger objects.  So if we are creating multiple
 			 * packs then we should modify the mtime of later ones
 			 * to preserve this property.
 			 */
 			if (stat(pack_tmp_name, &st) < 0) {
-				warning("failed to stat %s: %s",
-					pack_tmp_name, strerror(errno));
+				warning_errno("failed to stat %s", pack_tmp_name);
 			} else if (!last_mtime) {
 				last_mtime = st.st_mtime;
 			} else {
 				struct utimbuf utb;
 				utb.actime = st.st_atime;
 				utb.modtime = --last_mtime;
 				if (utime(pack_tmp_name, &utb) < 0)
-					warning("failed utime() on %s: %s",
-						pack_tmp_name, strerror(errno));
+					warning_errno("failed utime() on %s", pack_tmp_name);
 			}
 
 			strbuf_addf(&tmpname, "%s-", base_name);
 
 			if (write_bitmap_index) {
 				bitmap_writer_set_checksum(sha1);
