 	if (has_non_tip)
 		check_non_tip();
 
 	if (!use_sideband && daemon_mode)
 		no_progress = 1;
 
-	if (depth == 0 && shallows.nr == 0)
+	if (depth == 0 && !deepen_rev_list && shallows.nr == 0)
 		return;
-	if (depth > 0) {
-		struct commit_list *result = NULL, *backup = NULL;
+	if (depth > 0 && deepen_rev_list)
+		die("git upload-pack: deepen and deepen-since (or deepen-not) cannot be used together");
+	if (depth > 0)
+		deepen(depth, deepen_relative, &shallows);
+	else if (deepen_rev_list) {
+		struct argv_array av = ARGV_ARRAY_INIT;
 		int i;
-		if (depth == INFINITE_DEPTH && !is_repository_shallow())
-			for (i = 0; i < shallows.nr; i++) {
-				struct object *object = shallows.objects[i].item;
-				object->flags |= NOT_SHALLOW;
-			}
-		else
-			backup = result =
-				get_shallow_commits(&want_obj, depth,
-						    SHALLOW, NOT_SHALLOW);
-		while (result) {
-			struct object *object = &result->item->object;
-			if (!(object->flags & (CLIENT_SHALLOW|NOT_SHALLOW))) {
-				packet_write(1, "shallow %s",
-						oid_to_hex(&object->oid));
-				register_shallow(object->oid.hash);
-				shallow_nr++;
-			}
-			result = result->next;
-		}
-		free_commit_list(backup);
-		for (i = 0; i < shallows.nr; i++) {
-			struct object *object = shallows.objects[i].item;
-			if (object->flags & NOT_SHALLOW) {
-				struct commit_list *parents;
-				packet_write(1, "unshallow %s",
-					oid_to_hex(&object->oid));
-				object->flags &= ~CLIENT_SHALLOW;
-				/* make sure the real parents are parsed */
-				unregister_shallow(object->oid.hash);
-				object->parsed = 0;
-				parse_commit_or_die((struct commit *)object);
-				parents = ((struct commit *)object)->parents;
-				while (parents) {
-					add_object_array(&parents->item->object,
-							NULL, &want_obj);
-					parents = parents->next;
-				}
-				add_object_array(object, NULL, &extra_edge_obj);
-			}
-			/* make sure commit traversal conforms to client */
-			register_shallow(object->oid.hash);
+
+		argv_array_push(&av, "rev-list");
+		if (deepen_since)
+			argv_array_pushf(&av, "--max-age=%lu", deepen_since);
+		if (deepen_not.nr) {
+			argv_array_push(&av, "--not");
+			for (i = 0; i < deepen_not.nr; i++) {
+				struct string_list_item *s = deepen_not.items + i;
+				argv_array_push(&av, s->string);
+			}
+			argv_array_push(&av, "--not");
+		}
+		for (i = 0; i < want_obj.nr; i++) {
+			struct object *o = want_obj.objects[i].item;
+			argv_array_push(&av, oid_to_hex(&o->oid));
 		}
-		packet_flush(1);
-	} else
+		deepen_by_rev_list(av.argc, av.argv, &shallows);
+		argv_array_clear(&av);
+	}
+	else
 		if (shallows.nr > 0) {
 			int i;
 			for (i = 0; i < shallows.nr; i++)
 				register_shallow(shallows.objects[i].item->oid.hash);
 		}
 
