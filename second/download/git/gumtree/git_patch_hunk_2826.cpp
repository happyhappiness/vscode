 	if (obj->type == OBJ_COMMIT) {
 		struct commit *commit = (struct commit *) obj;
 
 		free_commit_buffer(commit);
 
 		if (!commit->parents && show_root)
-			printf("root %s\n", sha1_to_hex(commit->object.sha1));
+			printf("root %s\n", oid_to_hex(&commit->object.oid));
 	}
 
 	if (obj->type == OBJ_TAG) {
 		struct tag *tag = (struct tag *) obj;
 
 		if (show_tags && tag->tagged) {
-			printf("tagged %s %s", typename(tag->tagged->type), sha1_to_hex(tag->tagged->sha1));
-			printf(" (%s) in %s\n", tag->tag, sha1_to_hex(tag->object.sha1));
+			printf("tagged %s %s", typename(tag->tagged->type), oid_to_hex(&tag->tagged->oid));
+			printf(" (%s) in %s\n", tag->tag, oid_to_hex(&tag->object.oid));
 		}
 	}
 
 	return 0;
 }
 
