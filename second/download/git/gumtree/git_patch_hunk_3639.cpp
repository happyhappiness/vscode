 	if (obj->type == OBJ_COMMIT) {
 		struct commit *commit = (struct commit *) obj;
 
 		free_commit_buffer(commit);
 
 		if (!commit->parents && show_root)
-			printf("root %s\n", oid_to_hex(&commit->object.oid));
+			printf("root %s\n", describe_object(&commit->object));
 	}
 
 	if (obj->type == OBJ_TAG) {
 		struct tag *tag = (struct tag *) obj;
 
 		if (show_tags && tag->tagged) {
-			printf("tagged %s %s", typename(tag->tagged->type), oid_to_hex(&tag->tagged->oid));
-			printf(" (%s) in %s\n", tag->tag, oid_to_hex(&tag->object.oid));
+			printf("tagged %s %s", typename(tag->tagged->type),
+				describe_object(tag->tagged));
+			printf(" (%s) in %s\n", tag->tag,
+				describe_object(&tag->object));
 		}
 	}
 
 	return 0;
 }
 
