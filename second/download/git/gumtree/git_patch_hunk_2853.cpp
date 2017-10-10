 			break; /* found */
 	if (revs.nr <= i) {
 		ret = 1; /* not found */
 		goto cleanup_return;
 	}
 
-	printf("%s\n", sha1_to_hex(bases->item->object.sha1));
+	printf("%s\n", oid_to_hex(&bases->item->object.oid));
 
 cleanup_return:
 	free_commit_list(bases);
 	return ret;
 }
 
