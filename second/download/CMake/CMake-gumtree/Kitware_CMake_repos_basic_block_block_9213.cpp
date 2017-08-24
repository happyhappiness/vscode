{
		/*
		 * We are red and our parent is red, therefore we must have a
		 * grandfather and he must be black.
		 */
		grandpa = RB_FATHER(father);
		which = (father == grandpa->rb_right);
		other = which ^ RB_DIR_OTHER;
		uncle = grandpa->rb_nodes[other];

		if (RB_BLACK_P(uncle))
			break;

		/*
		 * Case 1: our uncle is red
		 *   Simply invert the colors of our parent and
		 *   uncle and make our grandparent red.  And
		 *   then solve the problem up at his level.
		 */
		RB_MARK_BLACK(uncle);
		RB_MARK_BLACK(father);
		if (RB_ROOT_P(rbt, grandpa)) {
			/*
			 * If our grandpa is root, don't bother
			 * setting him to red, just return.
			 */
			return;
		}
		RB_MARK_RED(grandpa);
		self = grandpa;
		father = RB_FATHER(self);
		if (RB_BLACK_P(father)) {
			/*
			 * If our great-grandpa is black, we're done.
			 */
			return;
		}
	}