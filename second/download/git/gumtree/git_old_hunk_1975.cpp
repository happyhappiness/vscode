	finish(head, remoteheads, result_commit, buf.buf);
	strbuf_release(&buf);
	drop_save();
	return 0;
}

static int suggest_conflicts(int renormalizing)
{
	const char *filename;
	FILE *fp;
	int pos;

	filename = git_path("MERGE_MSG");
	fp = fopen(filename, "a");
	if (!fp)
		die_errno(_("Could not open '%s' for writing"), filename);
	fprintf(fp, "\nConflicts:\n");
	for (pos = 0; pos < active_nr; pos++) {
		const struct cache_entry *ce = active_cache[pos];

		if (ce_stage(ce)) {
			fprintf(fp, "\t%s\n", ce->name);
			while (pos + 1 < active_nr &&
					!strcmp(ce->name,
						active_cache[pos + 1]->name))
				pos++;
		}
	}
	fclose(fp);
	rerere(allow_rerere_auto);
	printf(_("Automatic merge failed; "
			"fix conflicts and then commit the result.\n"));
	return 1;
}
