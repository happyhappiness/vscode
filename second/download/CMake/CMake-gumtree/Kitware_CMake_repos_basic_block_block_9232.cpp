{
		while (!RB_ROOT_P(rbt, self)) {
			if (other == (unsigned int)RB_POSITION(self))
				return RB_FATHER(self);
			self = RB_FATHER(self);
		}
		return NULL;
	}