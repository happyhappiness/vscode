 		value = argv[1];
 		oldval = argv[2];
 		if (get_sha1(value, sha1))
 			die("%s: not a valid SHA1", value);
 	}
 
-	hashclr(oldsha1); /* all-zero hash in case oldval is the empty string */
-	if (oldval && *oldval && get_sha1(oldval, oldsha1))
-		die("%s: not a valid old SHA1", oldval);
+	if (oldval) {
+		if (!*oldval)
+			/*
+			 * The empty string implies that the reference
+			 * must not already exist:
+			 */
+			hashclr(oldsha1);
+		else if (get_sha1(oldval, oldsha1))
+			die("%s: not a valid old SHA1", oldval);
+	}
 
 	if (no_deref)
 		flags = REF_NODEREF;
 	if (delete)
-		return delete_ref(refname, oldval ? oldsha1 : NULL, flags);
+		/*
+		 * For purposes of backwards compatibility, we treat
+		 * NULL_SHA1 as "don't care" here:
+		 */
+		return delete_ref(refname,
+				  (oldval && !is_null_sha1(oldsha1)) ? oldsha1 : NULL,
+				  flags);
 	else
 		return update_ref(msg, refname, sha1, oldval ? oldsha1 : NULL,
-				  flags, UPDATE_REFS_DIE_ON_ERR);
+				  flags | create_reflog_flag,
+				  UPDATE_REFS_DIE_ON_ERR);
 }
