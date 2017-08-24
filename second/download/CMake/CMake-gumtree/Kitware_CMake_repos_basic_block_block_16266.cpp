{
		/* Remove a child entry from sub-directory chain. */
		ent = parent->subdirs.first;
		while (ent->drnext != child)
			ent = ent->drnext;
		if ((ent->drnext = ent->drnext->drnext) == NULL)
			parent->subdirs.last = &(ent->drnext);
		parent->subdirs.cnt--;
	}