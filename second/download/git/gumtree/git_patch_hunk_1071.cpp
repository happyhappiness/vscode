 	 * the references that we are setting would have precedence
 	 * over our values. But some remote helpers create the remote
 	 * "HEAD" and "master" branches before calling this function,
 	 * so here we really only check that none of the references
 	 * that we are creating already exists.
 	 */
-	if (for_each_rawref(ref_present, &affected_refnames))
+	if (refs_for_each_rawref(&refs->base, ref_present,
+				 &affected_refnames))
 		die("BUG: initial ref transaction called with existing refs");
 
 	for (i = 0; i < transaction->nr; i++) {
 		struct ref_update *update = transaction->updates[i];
 
 		if ((update->flags & REF_HAVE_OLD) &&
 		    !is_null_sha1(update->old_sha1))
 			die("BUG: initial ref transaction with old_sha1 set");
-		if (verify_refname_available(update->refname,
-					     &affected_refnames, NULL,
-					     err)) {
+		if (refs_verify_refname_available(&refs->base, update->refname,
+						  &affected_refnames, NULL,
+						  err)) {
 			ret = TRANSACTION_NAME_CONFLICT;
 			goto cleanup;
 		}
 	}
 
 	if (lock_packed_refs(refs, 0)) {
