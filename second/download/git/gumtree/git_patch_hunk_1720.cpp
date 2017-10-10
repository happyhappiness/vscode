 		unsigned char read_sha1[20], tail_sha1[20];
 		struct strbuf msg = STRBUF_INIT;
 		int nr_unresolved = nr_deltas - nr_resolved_deltas;
 		int nr_objects_initial = nr_objects;
 		if (nr_unresolved <= 0)
 			die(_("confusion beyond insanity"));
-		objects = xrealloc(objects,
-				   (nr_objects + nr_unresolved + 1)
-				   * sizeof(*objects));
+		REALLOC_ARRAY(objects, nr_objects + nr_unresolved + 1);
 		memset(objects + nr_objects + 1, 0,
 		       nr_unresolved * sizeof(*objects));
 		f = sha1fd(output_fd, curr_pack);
 		fix_unresolved_deltas(f, nr_unresolved);
 		strbuf_addf(&msg, _("completed with %d local objects"),
 			    nr_objects - nr_objects_initial);
