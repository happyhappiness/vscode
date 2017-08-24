(RB_ROOT_P(rbt, grandpa)) {
			/*
			 * If our grandpa is root, don't bother
			 * setting him to red, just return.
			 */
			return;
		}