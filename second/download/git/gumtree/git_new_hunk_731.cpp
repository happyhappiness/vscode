		fprintf(stderr, "ignoring %.4s extension\n", ext);
		break;
	}
	return 0;
}

int hold_locked_index(struct lock_file *lk, int lock_flags)
{
	return hold_lock_file_for_update(lk, get_index_file(), lock_flags);
}

int read_index(struct index_state *istate)
{
	return read_index_from(istate, get_index_file());
}
