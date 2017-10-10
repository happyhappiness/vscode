 				describe_object(tag->tagged));
 			printf(" (%s) in %s\n", tag->tag,
 				describe_object(&tag->object));
 		}
 	}
 
-	return 0;
+out:
+	if (obj->type == OBJ_TREE)
+		free_tree_buffer((struct tree *)obj);
+	if (obj->type == OBJ_COMMIT)
+		free_commit_buffer((struct commit *)obj);
+	return err;
 }
 
 static int fsck_obj_buffer(const struct object_id *oid, enum object_type type,
 			   unsigned long size, void *buffer, int *eaten)
 {
 	/*
