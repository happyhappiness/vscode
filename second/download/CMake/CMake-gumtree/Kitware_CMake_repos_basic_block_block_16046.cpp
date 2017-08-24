{
		rr_parent = isoent->rr_parent;
		pxent = isoent->parent;
		if (rr_parent != NULL)
			isoent = rr_parent;
		else
			isoent = isoent->parent;
	}