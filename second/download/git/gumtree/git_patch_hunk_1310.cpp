 	}
 
 	commitname = (argc == 2) ? argv[1] : "HEAD";
 	if (get_oid(commitname, &oid))
 		die("Not a valid object name: '%s'", commitname);
 
-	derived = lookup_commit_reference(oid.hash);
+	derived = lookup_commit_reference(&oid);
 	memset(&revs, 0, sizeof(revs));
 	revs.initial = 1;
 	for_each_reflog_ent(refname, collect_one_reflog_ent, &revs);
 
 	if (!revs.nr && !get_oid(refname, &oid))
 		add_one_commit(&oid, &revs);
