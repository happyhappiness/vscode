 		else {
 			sha1 = ce->oid.hash;
 			mode = ce->ce_mode;
 			entlen = pathlen - baselen;
 			i++;
 		}
-		if (mode != S_IFGITLINK && !missing_ok && !has_sha1_file(sha1)) {
+
+		if (is_null_sha1(sha1) ||
+		    (mode != S_IFGITLINK && !missing_ok && !has_sha1_file(sha1))) {
 			strbuf_release(&buffer);
 			if (expected_missing)
 				return -1;
 			return error("invalid object %06o %s for '%.*s'",
 				mode, sha1_to_hex(sha1), entlen+baselen, path);
 		}
