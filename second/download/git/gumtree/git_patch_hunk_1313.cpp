 		usage_with_options(name_rev_usage, opts);
 	}
 	if (all || transform_stdin)
 		cutoff = 0;
 
 	for (; argc; argc--, argv++) {
-		unsigned char sha1[20];
+		struct object_id oid;
 		struct object *object;
 		struct commit *commit;
 
-		if (get_sha1(*argv, sha1)) {
+		if (get_oid(*argv, &oid)) {
 			fprintf(stderr, "Could not get sha1 for %s. Skipping.\n",
 					*argv);
 			continue;
 		}
 
 		commit = NULL;
-		object = parse_object(sha1);
+		object = parse_object(&oid);
 		if (object) {
 			struct object *peeled = deref_tag(object, *argv, 0);
 			if (peeled && peeled->type == OBJ_COMMIT)
 				commit = (struct commit *)peeled;
 		}
 
