 		switch (p->status) {
 		default:
 			die("internal error in blame::find_origin (%c)",
 			    p->status);
 		case 'M':
 			porigin = get_origin(sb, parent, origin->path);
-			hashcpy(porigin->blob_sha1, p->one->sha1);
+			hashcpy(porigin->blob_sha1, p->one->oid.hash);
 			porigin->mode = p->one->mode;
 			break;
 		case 'A':
 		case 'T':
 			/* Did not exist in parent, or type changed */
 			break;
 		}
 	}
 	diff_flush(&diff_opts);
-	free_pathspec(&diff_opts.pathspec);
+	clear_pathspec(&diff_opts.pathspec);
 	return porigin;
 }
 
 /*
  * We have an origin -- find the path that corresponds to it in its
  * parent and return an origin structure to represent it.
