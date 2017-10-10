 	}
 
 	argv_show_branch[1] = bisect_rev_hex;
 	return run_command_v_opt(argv_show_branch, RUN_GIT_CMD);
 }
 
-static struct commit *get_commit_reference(const unsigned char *sha1)
+static struct commit *get_commit_reference(const struct object_id *oid)
 {
-	struct commit *r = lookup_commit_reference(sha1);
+	struct commit *r = lookup_commit_reference(oid->hash);
 	if (!r)
-		die(_("Not a valid commit name %s"), sha1_to_hex(sha1));
+		die(_("Not a valid commit name %s"), oid_to_hex(oid));
 	return r;
 }
 
 static struct commit **get_bad_and_good_commits(int *rev_nr)
 {
 	struct commit **rev;
 	int i, n = 0;
 
 	ALLOC_ARRAY(rev, 1 + good_revs.nr);
-	rev[n++] = get_commit_reference(current_bad_oid->hash);
+	rev[n++] = get_commit_reference(current_bad_oid);
 	for (i = 0; i < good_revs.nr; i++)
-		rev[n++] = get_commit_reference(good_revs.sha1[i]);
+		rev[n++] = get_commit_reference(good_revs.oid + i);
 	*rev_nr = n;
 
 	return rev;
 }
 
 static void handle_bad_merge_base(void)
