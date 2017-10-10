 	}
 
 	close(fd);
 	free(path);
 }
 
-static void write_note_to_worktree(const unsigned char *obj,
-				   const unsigned char *note)
+static void write_note_to_worktree(const struct object_id *obj,
+				   const struct object_id *note)
 {
 	enum object_type type;
 	unsigned long size;
-	void *buf = read_sha1_file(note, &type, &size);
+	void *buf = read_sha1_file(note->hash, &type, &size);
 
 	if (!buf)
 		die("cannot read note %s for object %s",
-		    sha1_to_hex(note), sha1_to_hex(obj));
+		    oid_to_hex(note), oid_to_hex(obj));
 	if (type != OBJ_BLOB)
 		die("blob expected in note %s for object %s",
-		    sha1_to_hex(note), sha1_to_hex(obj));
+		    oid_to_hex(note), oid_to_hex(obj));
 	write_buf_to_worktree(obj, buf, size);
 	free(buf);
 }
 
 static int ll_merge_in_worktree(struct notes_merge_options *o,
 				struct notes_merge_pair *p)
