{
		*parent->subdirs.last = child;
		parent->subdirs.last = &(child->drnext);
		parent->subdirs.cnt++;
		child->parent = parent;
	}