 		}
 		else {
 			/* mode ' ' sha1 '\t' name
 			 * ptr[-1] points at tab,
 			 * ptr[-41] is at the beginning of sha1
 			 */
-			ptr[-42] = ptr[-1] = 0;
-			if (add_cacheinfo(mode, sha1, path_name, stage))
+			ptr[-(GIT_SHA1_HEXSZ + 2)] = ptr[-1] = 0;
+			if (add_cacheinfo(mode, &oid, path_name, stage))
 				die("git update-index: unable to update %s",
 				    path_name);
 		}
 		continue;
 
 	bad_line:
