(standin_father != self) {
			/*
			 * Change the son's parentage to point to his grandpa.
			 */
			RB_SET_FATHER(standin_son, standin_father);
			RB_SET_POSITION(standin_son, standin_which);
		}