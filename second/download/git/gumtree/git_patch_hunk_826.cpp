 	free(idx);
 	return tmpfile;
 }
 
 static char *keep_pack(const char *curr_index_name)
 {
-	static char name[PATH_MAX];
 	static const char *keep_msg = "fast-import";
+	struct strbuf name = STRBUF_INIT;
 	int keep_fd;
 
-	keep_fd = odb_pack_keep(name, sizeof(name), pack_data->sha1);
+	odb_pack_name(&name, pack_data->sha1, "keep");
+	keep_fd = odb_pack_keep(name.buf);
 	if (keep_fd < 0)
 		die_errno("cannot create keep file");
 	write_or_die(keep_fd, keep_msg, strlen(keep_msg));
 	if (close(keep_fd))
 		die_errno("failed to write keep file");
 
-	snprintf(name, sizeof(name), "%s/pack/pack-%s.pack",
-		 get_object_directory(), sha1_to_hex(pack_data->sha1));
-	if (finalize_object_file(pack_data->pack_name, name))
+	odb_pack_name(&name, pack_data->sha1, "pack");
+	if (finalize_object_file(pack_data->pack_name, name.buf))
 		die("cannot store pack file");
 
-	snprintf(name, sizeof(name), "%s/pack/pack-%s.idx",
-		 get_object_directory(), sha1_to_hex(pack_data->sha1));
-	if (finalize_object_file(curr_index_name, name))
+	odb_pack_name(&name, pack_data->sha1, "idx");
+	if (finalize_object_file(curr_index_name, name.buf))
 		die("cannot store index file");
 	free((void *)curr_index_name);
-	return name;
+	return strbuf_detach(&name, NULL);
 }
 
 static void unkeep_all_packs(void)
 {
-	static char name[PATH_MAX];
+	struct strbuf name = STRBUF_INIT;
 	int k;
 
 	for (k = 0; k < pack_id; k++) {
 		struct packed_git *p = all_packs[k];
-		snprintf(name, sizeof(name), "%s/pack/pack-%s.keep",
-			 get_object_directory(), sha1_to_hex(p->sha1));
-		unlink_or_warn(name);
+		odb_pack_name(&name, p->sha1, "keep");
+		unlink_or_warn(name.buf);
 	}
+	strbuf_release(&name);
 }
 
 static int loosen_small_pack(const struct packed_git *p)
 {
 	struct child_process unpack = CHILD_PROCESS_INIT;
 
