 
 			rev[i] = merge_base->item;
 		}
 
 		if (rev_nr % 2)
 			rev[i] = rev[2 * i];
-		rev_nr = (rev_nr + 1) / 2;
+		rev_nr = DIV_ROUND_UP(rev_nr, 2);
 	}
 
 	if (!in_merge_bases(base, rev[0]))
 		die(_("base commit should be the ancestor of revision list"));
 
 	for (i = 0; i < total; i++) {
