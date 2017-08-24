(!match_owner_id(&(a->inclusion_uids),
		    archive_entry_uid(entry)))
			return (1);