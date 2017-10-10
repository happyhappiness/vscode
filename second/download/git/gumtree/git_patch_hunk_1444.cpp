 		free(buf);
 }
 
 static void parse_get_mark(const char *p)
 {
 	struct object_entry *oe = oe;
-	char output[42];
+	char output[GIT_MAX_HEXSZ + 2];
 
 	/* get-mark SP <object> LF */
 	if (*p != ':')
 		die("Not a mark: %s", p);
 
 	oe = find_mark(parse_mark_ref_eol(p));
 	if (!oe)
 		die("Unknown mark: %s", command_buf.buf);
 
-	xsnprintf(output, sizeof(output), "%s\n", sha1_to_hex(oe->idx.sha1));
-	cat_blob_write(output, 41);
+	xsnprintf(output, sizeof(output), "%s\n", oid_to_hex(&oe->idx.oid));
+	cat_blob_write(output, GIT_SHA1_HEXSZ + 1);
 }
 
 static void parse_cat_blob(const char *p)
 {
 	struct object_entry *oe = oe;
-	unsigned char sha1[20];
+	struct object_id oid;
 
 	/* cat-blob SP <object> LF */
 	if (*p == ':') {
 		oe = find_mark(parse_mark_ref_eol(p));
 		if (!oe)
 			die("Unknown mark: %s", command_buf.buf);
-		hashcpy(sha1, oe->idx.sha1);
+		oidcpy(&oid, &oe->idx.oid);
 	} else {
-		if (get_sha1_hex(p, sha1))
+		if (parse_oid_hex(p, &oid, &p))
 			die("Invalid dataref: %s", command_buf.buf);
-		if (p[40])
+		if (*p)
 			die("Garbage after SHA1: %s", command_buf.buf);
-		oe = find_object(sha1);
+		oe = find_object(&oid);
 	}
 
-	cat_blob(oe, sha1);
+	cat_blob(oe, &oid);
 }
 
 static struct object_entry *dereference(struct object_entry *oe,
-					unsigned char sha1[20])
+					struct object_id *oid)
 {
 	unsigned long size;
 	char *buf = NULL;
 	if (!oe) {
-		enum object_type type = sha1_object_info(sha1, NULL);
+		enum object_type type = sha1_object_info(oid->hash, NULL);
 		if (type < 0)
-			die("object not found: %s", sha1_to_hex(sha1));
+			die("object not found: %s", oid_to_hex(oid));
 		/* cache it! */
-		oe = insert_object(sha1);
+		oe = insert_object(oid);
 		oe->type = type;
 		oe->pack_id = MAX_PACK_ID;
 		oe->idx.offset = 1;
 	}
 	switch (oe->type) {
 	case OBJ_TREE:	/* easy case. */
