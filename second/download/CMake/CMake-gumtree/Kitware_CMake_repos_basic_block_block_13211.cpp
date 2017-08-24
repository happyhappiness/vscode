(nx = &(xar->file->xattr_list);
	    *nx != NULL; nx = &((*nx)->next)) {
		if (xattr->id < (*nx)->id)
			break;
	}