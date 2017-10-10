 		fprintf(fp, "--shallow %s\n", sha1_to_hex(graft->sha1));
 	return 0;
 }
 
 static void create_pack_file(void)
 {
-	struct child_process pack_objects;
+	struct child_process pack_objects = CHILD_PROCESS_INIT;
 	char data[8193], progress[128];
 	char abort_msg[] = "aborting due to possible repository "
 		"corruption on the remote side.";
 	int buffered = -1;
 	ssize_t sz;
 	const char *argv[12];
