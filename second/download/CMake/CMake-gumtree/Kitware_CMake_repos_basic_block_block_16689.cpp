(mtree->set.keys & F_FLAGS) {
		if (mtree->set.fflags_set == me->fflags_set &&
		    mtree->set.fflags_clear == me->fflags_clear)
			keys &= ~F_FLAGS;
	}