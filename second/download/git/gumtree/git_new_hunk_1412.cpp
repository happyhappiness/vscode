		    fill_mmfile(&mf2, p->two) < 0)
			return error("unable to read files to diff");

		if (diff_filespec_is_binary(p->one) ||
		    diff_filespec_is_binary(p->two)) {
			git_SHA1_Update(&ctx, oid_to_hex(&p->one->oid),
					GIT_SHA1_HEXSZ);
			git_SHA1_Update(&ctx, oid_to_hex(&p->two->oid),
					GIT_SHA1_HEXSZ);
			continue;
		}

		xpp.flags = 0;
		xecfg.ctxlen = 3;
		xecfg.flags = 0;
		if (xdi_diff_outf(&mf1, &mf2, patch_id_consume, &data,
				  &xpp, &xecfg))
			return error("unable to generate patch-id diff for %s",
				     p->one->path);
	}

	git_SHA1_Final(oid->hash, &ctx);
	return 0;
}

int diff_flush_patch_id(struct diff_options *options, struct object_id *oid, int diff_header_only)
{
	struct diff_queue_struct *q = &diff_queued_diff;
	int i;
	int result = diff_get_patch_id(options, oid, diff_header_only);

	for (i = 0; i < q->nr; i++)
		diff_free_filepair(q->queue[i]);

	free(q->queue);
	DIFF_QUEUE_CLEAR(q);
