 		die(_("Need exactly one range."));
 
 	o1 = rev->pending.objects[0].item;
 	o2 = rev->pending.objects[1].item;
 	flags1 = o1->flags;
 	flags2 = o2->flags;
-	c1 = lookup_commit_reference(o1->sha1);
-	c2 = lookup_commit_reference(o2->sha1);
+	c1 = lookup_commit_reference(o1->oid.hash);
+	c2 = lookup_commit_reference(o2->oid.hash);
 
 	if ((flags1 & UNINTERESTING) == (flags2 & UNINTERESTING))
 		die(_("Not a range."));
 
 	init_patch_ids(ids);
 
