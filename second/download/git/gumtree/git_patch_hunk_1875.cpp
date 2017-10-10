 		return 0;
 	}
 	if (!has_sha1_file(entry->u.value.sha1)) {
 		unsigned char sha1[20];
 		int flags;
 
-		if (read_ref_full(entry->name, sha1, 0, &flags))
+		if (read_ref_full(entry->name, 0, sha1, &flags))
 			/* We should at least have found the packed ref. */
 			die("Internal error");
 		if ((flags & REF_ISSYMREF) || !(flags & REF_ISPACKED)) {
 			/*
 			 * This packed reference is overridden by a
 			 * loose reference, so it is OK that its value
