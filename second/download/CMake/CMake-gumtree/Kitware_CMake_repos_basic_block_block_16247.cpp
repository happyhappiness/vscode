{
			nf->hardlink_target = target;
			archive_entry_set_nlink(nf->entry, hl->nlink);
		}