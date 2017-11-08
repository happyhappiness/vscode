static void wt_porcelain_v2_print_unmerged_entry(
	struct string_list_item *it,
	struct wt_status *s)
{
	struct wt_status_change_data *d = it->util;
	const struct cache_entry *ce;
	struct strbuf buf_index = STRBUF_INIT;
	const char *path_index = NULL;
	int pos, stage, sum;
	struct {
		int mode;
		struct object_id oid;
	} stages[3];
	char *key;
	char submodule_token[5];
	char unmerged_prefix = 'u';
	char eol_char = s->null_termination ? '\0' : '\n';

	wt_porcelain_v2_submodule_state(d, submodule_token);

	switch (d->stagemask) {
	case 1: key = "DD"; break; /* both deleted */
	case 2: key = "AU"; break; /* added by us */
	case 3: key = "UD"; break; /* deleted by them */
	case 4: key = "UA"; break; /* added by them */
	case 5: key = "DU"; break; /* deleted by us */
	case 6: key = "AA"; break; /* both added */
	case 7: key = "UU"; break; /* both modified */
	default:
		die("BUG: unhandled unmerged status %x", d->stagemask);
	}

	/*
	 * Disregard d.aux.porcelain_v2 data that we accumulated
	 * for the head and index columns during the scans and
	 * replace with the actual stage data.
	 *
	 * Note that this is a last-one-wins for each the individual
	 * stage [123] columns in the event of multiple cache entries
	 * for same stage.
	 */
	memset(stages, 0, sizeof(stages));
	sum = 0;
	pos = cache_name_pos(it->string, strlen(it->string));
	assert(pos < 0);
	pos = -pos-1;
	while (pos < active_nr) {
		ce = active_cache[pos++];
		stage = ce_stage(ce);
		if (strcmp(ce->name, it->string) || !stage)
			break;
		stages[stage - 1].mode = ce->ce_mode;
		hashcpy(stages[stage - 1].oid.hash, ce->oid.hash);
		sum |= (1 << (stage - 1));
	}
	if (sum != d->stagemask)
		die("BUG: observed stagemask 0x%x != expected stagemask 0x%x", sum, d->stagemask);

	if (s->null_termination)
		path_index = it->string;
	else
		path_index = quote_path(it->string, s->prefix, &buf_index);

	fprintf(s->fp, "%c %s %s %06o %06o %06o %06o %s %s %s %s%c",
			unmerged_prefix, key, submodule_token,
			stages[0].mode, /* stage 1 */
			stages[1].mode, /* stage 2 */
			stages[2].mode, /* stage 3 */
			d->mode_worktree,
			oid_to_hex(&stages[0].oid), /* stage 1 */
			oid_to_hex(&stages[1].oid), /* stage 2 */
			oid_to_hex(&stages[2].oid), /* stage 3 */
			path_index,
			eol_char);

	strbuf_release(&buf_index);
}