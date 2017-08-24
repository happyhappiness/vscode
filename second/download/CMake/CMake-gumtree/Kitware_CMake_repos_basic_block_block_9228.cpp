(RB_BLACK_P(parent)
		    && RB_BLACK_P(brother->rb_left)
		    && RB_BLACK_P(brother->rb_right)) {
			if (RB_RED_P(brother)) {
				/*
				 * Case 1: Our brother is red, swap its
				 * position (and colors) with our parent. 
				 * This should now be case 2b (unless C or E
				 * has a red child which is case 3; thus no
				 * explicit branch to case 2b).
				 *
				 *    B         ->        D
				 *  A     d     ->    b     E
				 *      C   E   ->  A   C
				 */
				__archive_rb_tree_reparent_nodes(parent, other);
				brother = parent->rb_nodes[other];
				if (brother == NULL)
					return;/* The tree may be broken. */
			} else {
				/*
				 * Both our parent and brother are black.
				 * Change our brother to red, advance up rank
				 * and go through the loop again.
				 *
				 *    B         ->   *B
				 * *A     D     ->  A     d
				 *      C   E   ->      C   E
				 */
				RB_MARK_RED(brother);
				if (RB_ROOT_P(rbt, parent))
					return;	/* root == parent == black */
				which = RB_POSITION(parent);
				parent = RB_FATHER(parent);
				continue;
			}
		}