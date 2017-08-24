(; np != NULL; np = np->ptnext) {
			struct isoent *mvent;
			struct isoent *newent;

			if (!np->dir)
				continue;
			for (mvent = np->subdirs.first;
			    mvent != NULL; mvent = mvent->drnext) {
				r = isoent_rr_move_dir(a, &rr_moved,
				    mvent, &newent);
				if (r < 0)
					return (r);
				isoent_collect_dirs(&(iso9660->primary),
				    newent, 2);
			}
		}