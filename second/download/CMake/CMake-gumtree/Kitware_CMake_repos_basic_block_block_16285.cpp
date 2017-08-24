{
		_isoent_file_location(iso9660, np, &symlocation);

		if (np->subdirs.first != NULL &&
		    (joliet ||
		    ((iso9660->opt.rr == OPT_RR_DISABLED &&
		      depth + 2 < iso9660->primary.max_depth) ||
		     (iso9660->opt.rr &&
		      depth + 1 < iso9660->primary.max_depth)))) {
			/* Enter to sub directories. */
			np = np->subdirs.first;
			depth++;
			continue;
		}
		while (np != np->parent) {
			if (np->drnext == NULL) {
				/* Return to the parent directory. */
				np = np->parent;
				depth--;
			} else {
				np = np->drnext;
				break;
			}
		}
	}