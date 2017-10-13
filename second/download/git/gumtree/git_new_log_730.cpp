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