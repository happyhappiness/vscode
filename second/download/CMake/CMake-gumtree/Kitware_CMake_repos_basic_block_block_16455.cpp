{
		/*
		 * It's necessary that rr_move is the first entry
		 * of the root.
		 */
		/* Remove "rr_moved" entry from children chain. */
		isoent_remove_child(rootent, rr_moved);

		/* Add "rr_moved" entry into the head of children chain. */
		isoent_add_child_head(rootent, rr_moved);
	}