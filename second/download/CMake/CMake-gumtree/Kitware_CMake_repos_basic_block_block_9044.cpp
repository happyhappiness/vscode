(!match_owner_id(&(a->inclusion_gids),
		    archive_entry_gid(entry)))
			return (1);