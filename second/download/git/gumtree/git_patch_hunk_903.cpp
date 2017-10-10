 	if (!f)
 		die_errno("cannot read '%s'", input_file);
 
 	while (fgets(line, sizeof(line), f)) {
 		uint32_t mark;
 		char *line_end, *mark_end;
-		unsigned char sha1[20];
+		struct object_id oid;
 		struct object *object;
 		struct commit *commit;
 		enum object_type type;
 
 		line_end = strchr(line, '\n');
 		if (line[0] != ':' || !line_end)
 			die("corrupt mark line: %s", line);
 		*line_end = '\0';
 
 		mark = strtoumax(line + 1, &mark_end, 10);
 		if (!mark || mark_end == line + 1
-			|| *mark_end != ' ' || get_sha1_hex(mark_end + 1, sha1))
+			|| *mark_end != ' ' || get_oid_hex(mark_end + 1, &oid))
 			die("corrupt mark line: %s", line);
 
 		if (last_idnum < mark)
 			last_idnum = mark;
 
-		type = sha1_object_info(sha1, NULL);
+		type = sha1_object_info(oid.hash, NULL);
 		if (type < 0)
-			die("object not found: %s", sha1_to_hex(sha1));
+			die("object not found: %s", oid_to_hex(&oid));
 
 		if (type != OBJ_COMMIT)
 			/* only commits */
 			continue;
 
-		commit = lookup_commit(sha1);
+		commit = lookup_commit(oid.hash);
 		if (!commit)
-			die("not a commit? can't happen: %s", sha1_to_hex(sha1));
+			die("not a commit? can't happen: %s", oid_to_hex(&oid));
 
 		object = &commit->object;
 
 		if (object->flags & SHOWN)
-			error("Object %s already has a mark", sha1_to_hex(sha1));
+			error("Object %s already has a mark", oid_to_hex(&oid));
 
 		mark_object(object, mark);
 
 		object->flags |= SHOWN;
 	}
 	fclose(f);
