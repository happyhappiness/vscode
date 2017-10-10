		die("BUG: initial ref transaction called with existing refs");

	for (i = 0; i < transaction->nr; i++) {
		struct ref_update *update = transaction->updates[i];

		if ((update->flags & REF_HAVE_OLD) &&
		    !is_null_sha1(update->old_sha1))
			die("BUG: initial ref transaction with old_sha1 set");
		if (refs_verify_refname_available(&refs->base, update->refname,
						  &affected_refnames, NULL,
						  err)) {
			ret = TRANSACTION_NAME_CONFLICT;
			goto cleanup;
