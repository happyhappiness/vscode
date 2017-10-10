			/* same change in local and remote; nothing to do */
			trace_printf("\t\t\tskipping (local == remote)\n");
		} else if (!oidcmp(&p->local, &uninitialized) ||
			   !oidcmp(&p->local, &p->base)) {
			/* no local change; adopt remote change */
			trace_printf("\t\t\tno local change, adopted remote\n");
			if (add_note(t, p->obj.hash, p->remote.hash,
				     combine_notes_overwrite))
				die("BUG: combine_notes_overwrite failed");
		} else {
			/* need file-level merge between local and remote */
			trace_printf("\t\t\tneed content-level merge\n");
			conflicts += merge_one_change(o, p, t);
