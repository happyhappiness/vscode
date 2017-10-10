 			struct object_id oid;
 			if (argc <= ++i)
 				usage(commit_tree_usage);
 			if (get_sha1_commit(argv[i], oid.hash))
 				die("Not a valid object name %s", argv[i]);
 			assert_sha1_type(oid.hash, OBJ_COMMIT);
-			new_parent(lookup_commit(oid.hash), &parents);
+			new_parent(lookup_commit(&oid), &parents);
 			continue;
 		}
 
 		if (skip_prefix(arg, "-S", &sign_commit))
 			continue;
 
