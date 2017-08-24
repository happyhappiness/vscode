{
		isoent_free_all(iso9660->joliet.rootent);
		for (i = 0; i < iso9660->joliet.max_depth; i++)
			free(iso9660->joliet.pathtbl[i].sorted);
		free(iso9660->joliet.pathtbl);
	}