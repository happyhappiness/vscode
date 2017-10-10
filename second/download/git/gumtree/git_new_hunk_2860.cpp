		usage_with_options(builtin_merge_usage,
			builtin_merge_options);

	if (verify_signatures) {
		for (p = remoteheads; p; p = p->next) {
			struct commit *commit = p->item;
			char hex[GIT_SHA1_HEXSZ + 1];
			struct signature_check signature_check;
			memset(&signature_check, 0, sizeof(signature_check));

			check_commit_signature(commit, &signature_check);

			find_unique_abbrev_r(hex, commit->object.oid.hash, DEFAULT_ABBREV);
			switch (signature_check.result) {
			case 'G':
				break;
			case 'U':
				die(_("Commit %s has an untrusted GPG signature, "
				      "allegedly by %s."), hex, signature_check.signer);
