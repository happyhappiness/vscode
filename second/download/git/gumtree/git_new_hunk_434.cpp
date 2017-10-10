	}

	/* Grab blobs from given path from HEAD and MERGE_HEAD,
	 * stuff HEAD version in stage #2,
	 * stuff MERGE_HEAD version in stage #3.
	 */
	ce_2 = read_one_ent("our", &head_oid, path, namelen, 2);
	ce_3 = read_one_ent("their", &merge_head_oid, path, namelen, 3);

	if (!ce_2 || !ce_3) {
		ret = -1;
		goto free_return;
	}
	if (!oidcmp(&ce_2->oid, &ce_3->oid) &&
	    ce_2->ce_mode == ce_3->ce_mode) {
		fprintf(stderr, "%s: identical in both, skipping.\n",
			path);
		goto free_return;
	}

