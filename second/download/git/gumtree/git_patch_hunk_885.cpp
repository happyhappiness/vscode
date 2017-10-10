 	return seen_commits;
 }
 
 static void display_name(struct commit_name *n)
 {
 	if (n->prio == 2 && !n->tag) {
-		n->tag = lookup_tag(n->sha1);
+		n->tag = lookup_tag(n->oid.hash);
 		if (!n->tag || parse_tag(n->tag))
 			die(_("annotated tag %s not available"), n->path);
 	}
 	if (n->tag && !n->name_checked) {
 		if (!n->tag->tag)
 			die(_("annotated tag %s has no embedded name"), n->path);
