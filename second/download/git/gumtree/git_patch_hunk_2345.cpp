 }
 
 static int write_one_shallow(const struct commit_graft *graft, void *cb_data)
 {
 	FILE *fp = cb_data;
 	if (graft->nr_parent == -1)
-		fprintf(fp, "--shallow %s\n", sha1_to_hex(graft->sha1));
+		fprintf(fp, "--shallow %s\n", oid_to_hex(&graft->oid));
 	return 0;
 }
 
 static void create_pack_file(void)
 {
 	struct child_process pack_objects = CHILD_PROCESS_INIT;
