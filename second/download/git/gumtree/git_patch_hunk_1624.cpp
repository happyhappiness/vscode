 		for (i = 0; i < refspec_nr; i++) {
 			struct refspec *rs = refspec + i;
 
 			if (rs->pattern || rs->matching)
 				continue;
 
-			/*
-			 * LHS must match a single ref
-			 * NEEDSWORK: add logic to special case 'HEAD' once
-			 * working with submodules in a detached head state
-			 * ceases to be the norm.
-			 */
-			if (count_refspec_match(rs->src, local_refs, NULL) != 1)
+			/* LHS must match a single ref */
+			switch (count_refspec_match(rs->src, local_refs, NULL)) {
+			case 1:
+				break;
+			case 0:
+				/*
+				 * If LHS matches 'HEAD' then we need to ensure
+				 * that it matches the same named branch
+				 * checked out in the superproject.
+				 */
+				if (!strcmp(rs->src, "HEAD")) {
+					if (!detached_head &&
+					    !strcmp(head, superproject_head))
+						break;
+					die("HEAD does not match the named branch in the superproject");
+				}
+			default:
 				die("src refspec '%s' must name a ref",
 				    rs->src);
+			}
 		}
 		free_refspec(refspec_nr, refspec);
 	}
+	free(head);
 
 	return 0;
 }
 
 static int absorb_git_dirs(int argc, const char **argv, const char *prefix)
 {
