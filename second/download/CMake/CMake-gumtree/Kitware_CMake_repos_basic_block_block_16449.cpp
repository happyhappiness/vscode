{
		struct isoent *rootent = iso9660->primary.rootent;
		/* There isn't rr_move entry.
		 * Create rr_move entry and insert it into the root entry.
		 */
		rrmoved = isoent_create_virtual_dir(a, iso9660, "rr_moved");
		if (rrmoved == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory");
			return (ARCHIVE_FATAL);
		}
		/* Add "rr_moved" entry to the root entry. */
		isoent_add_child_head(rootent, rrmoved);
		archive_entry_set_nlink(rootent->file->entry,
		    archive_entry_nlink(rootent->file->entry) + 1);
		/* Register "rr_moved" entry to second level pathtable. */
		path_table_add_entry(&(iso9660->primary.pathtbl[1]), rrmoved);
		/* Save rr_moved. */
		*rr_moved = rrmoved;
	}