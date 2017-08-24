{
		if ((child->drnext = parent->subdirs.first) == NULL)
			parent->subdirs.last = &(child->drnext);
		parent->subdirs.first = child;
		parent->subdirs.cnt++;
		child->parent = parent;
	}