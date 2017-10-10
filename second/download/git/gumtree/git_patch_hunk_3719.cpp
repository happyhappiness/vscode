 	}
 	warning("Illegal crlf_action %d\n", (int)crlf_action);
 	return core_eol;
 }
 
 static void check_safe_crlf(const char *path, enum crlf_action crlf_action,
-                            struct text_stat *stats, enum safe_crlf checksafe)
+			    struct text_stat *old_stats, struct text_stat *new_stats,
+			    enum safe_crlf checksafe)
 {
-	if (!checksafe)
-		return;
-
-	if (output_eol(crlf_action) == EOL_LF) {
+	if (old_stats->crlf && !new_stats->crlf ) {
 		/*
-		 * CRLFs would not be restored by checkout:
-		 * check if we'd remove CRLFs
+		 * CRLFs would not be restored by checkout
 		 */
-		if (stats->crlf) {
-			if (checksafe == SAFE_CRLF_WARN)
-				warning("CRLF will be replaced by LF in %s.\nThe file will have its original line endings in your working directory.", path);
-			else /* i.e. SAFE_CRLF_FAIL */
-				die("CRLF would be replaced by LF in %s.", path);
-		}
-	} else if (output_eol(crlf_action) == EOL_CRLF) {
+		if (checksafe == SAFE_CRLF_WARN)
+			warning("CRLF will be replaced by LF in %s.\nThe file will have its original line endings in your working directory.", path);
+		else /* i.e. SAFE_CRLF_FAIL */
+			die("CRLF would be replaced by LF in %s.", path);
+	} else if (old_stats->lonelf && !new_stats->lonelf ) {
 		/*
-		 * CRLFs would be added by checkout:
-		 * check if we have "naked" LFs
+		 * CRLFs would be added by checkout
 		 */
-		if (stats->lonelf) {
-			if (checksafe == SAFE_CRLF_WARN)
-				warning("LF will be replaced by CRLF in %s.\nThe file will have its original line endings in your working directory.", path);
-			else /* i.e. SAFE_CRLF_FAIL */
-				die("LF would be replaced by CRLF in %s", path);
-		}
+		if (checksafe == SAFE_CRLF_WARN)
+			warning("LF will be replaced by CRLF in %s.\nThe file will have its original line endings in your working directory.", path);
+		else /* i.e. SAFE_CRLF_FAIL */
+			die("LF would be replaced by CRLF in %s", path);
 	}
 }
 
 static int has_cr_in_index(const char *path)
 {
 	unsigned long sz;
