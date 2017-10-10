 
 	return msg_type;
 }
 
 static void init_skiplist(struct fsck_options *options, const char *path)
 {
-	static struct sha1_array skiplist = SHA1_ARRAY_INIT;
+	static struct oid_array skiplist = OID_ARRAY_INIT;
 	int sorted, fd;
-	char buffer[41];
-	unsigned char sha1[20];
+	char buffer[GIT_MAX_HEXSZ + 1];
+	struct object_id oid;
 
 	if (options->skiplist)
 		sorted = options->skiplist->sorted;
 	else {
 		sorted = 1;
 		options->skiplist = &skiplist;
 	}
 
 	fd = open(path, O_RDONLY);
 	if (fd < 0)
 		die("Could not open skip list: %s", path);
 	for (;;) {
+		const char *p;
 		int result = read_in_full(fd, buffer, sizeof(buffer));
 		if (result < 0)
 			die_errno("Could not read '%s'", path);
 		if (!result)
 			break;
-		if (get_sha1_hex(buffer, sha1) || buffer[40] != '\n')
+		if (parse_oid_hex(buffer, &oid, &p) || *p != '\n')
 			die("Invalid SHA-1: %s", buffer);
-		sha1_array_append(&skiplist, sha1);
+		oid_array_append(&skiplist, &oid);
 		if (sorted && skiplist.nr > 1 &&
-				hashcmp(skiplist.sha1[skiplist.nr - 2],
-					sha1) > 0)
+				oidcmp(&skiplist.oid[skiplist.nr - 2],
+				       &oid) > 0)
 			sorted = 0;
 	}
 	close(fd);
 
 	if (sorted)
 		skiplist.sorted = 1;
