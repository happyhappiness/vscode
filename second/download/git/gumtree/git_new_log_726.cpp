fprintf(s->fp, "2 %s %s %06o %06o %06o %s %s %c%d %s%c%s%c",
				key, submodule_token,
				d->mode_head, d->mode_index, d->mode_worktree,
				oid_to_hex(&d->oid_head), oid_to_hex(&d->oid_index),
				key[0], d->score,
				path_index, sep_char, path_head, eol_char);