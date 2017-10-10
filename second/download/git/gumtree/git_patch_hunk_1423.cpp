 
 	fprintf(rpt, "  status      :");
 	if (b->active)
 		fputs(" active", rpt);
 	if (b->branch_tree.tree)
 		fputs(" loaded", rpt);
-	if (is_null_sha1(b->branch_tree.versions[1].sha1))
+	if (is_null_oid(&b->branch_tree.versions[1].oid))
 		fputs(" dirty", rpt);
 	fputc('\n', rpt);
 
-	fprintf(rpt, "  tip commit  : %s\n", sha1_to_hex(b->sha1));
-	fprintf(rpt, "  old tree    : %s\n", sha1_to_hex(b->branch_tree.versions[0].sha1));
-	fprintf(rpt, "  cur tree    : %s\n", sha1_to_hex(b->branch_tree.versions[1].sha1));
+	fprintf(rpt, "  tip commit  : %s\n", oid_to_hex(&b->oid));
+	fprintf(rpt, "  old tree    : %s\n",
+		oid_to_hex(&b->branch_tree.versions[0].oid));
+	fprintf(rpt, "  cur tree    : %s\n",
+		oid_to_hex(&b->branch_tree.versions[1].oid));
 	fprintf(rpt, "  commit clock: %" PRIuMAX "\n", b->last_commit);
 
 	fputs("  last pack   : ", rpt);
 	if (b->pack_id < MAX_PACK_ID)
 		fprintf(rpt, "%u", b->pack_id);
 	fputc('\n', rpt);
