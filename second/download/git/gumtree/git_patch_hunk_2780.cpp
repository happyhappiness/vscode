 						    path, contents_from);
 		add_pending_object(&revs, &(sb.final->object), ":");
 	}
 	else if (contents_from)
 		die("Cannot use --contents with final commit object name");
 
+	if (reverse && revs.first_parent_only) {
+		final_commit = find_single_final(sb.revs, NULL);
+		if (!final_commit)
+			die("--reverse and --first-parent together require specified latest commit");
+	}
+
 	/*
 	 * If we have bottom, this will mark the ancestors of the
 	 * bottom commits we would reach while traversing as
 	 * uninteresting.
 	 */
 	if (prepare_revision_walk(&revs))
 		die(_("revision walk setup failed"));
 
-	if (is_null_sha1(sb.final->object.sha1)) {
+	if (reverse && revs.first_parent_only) {
+		struct commit *c = final_commit;
+
+		sb.revs->children.name = "children";
+		while (c->parents &&
+		       oidcmp(&c->object.oid, &sb.final->object.oid)) {
+			struct commit_list *l = xcalloc(1, sizeof(*l));
+
+			l->item = c;
+			if (add_decoration(&sb.revs->children,
+					   &c->parents->item->object, l))
+				die("BUG: not unique item in first-parent chain");
+			c = c->parents->item;
+		}
+
+		if (oidcmp(&c->object.oid, &sb.final->object.oid))
+			die("--reverse --first-parent together require range along first-parent chain");
+	}
+
+	if (is_null_oid(&sb.final->object.oid)) {
 		o = sb.final->util;
 		sb.final_buf = xmemdupz(o->file.ptr, o->file.size);
 		sb.final_buf_size = o->file.size;
 	}
 	else {
 		o = get_origin(&sb, sb.final, path);
