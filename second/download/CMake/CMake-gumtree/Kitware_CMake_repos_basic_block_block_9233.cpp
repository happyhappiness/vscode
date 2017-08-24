{
	const unsigned int other = direction ^ RB_DIR_OTHER;

	if (self == NULL) {
		self = rbt->rbt_root;
		if (RB_SENTINEL_P(self))
			return NULL;
		while (!RB_SENTINEL_P(self->rb_nodes[direction]))
			self = self->rb_nodes[direction];
		return self;
	}
	/*
	 * We can't go any further in this direction.  We proceed up in the
	 * opposite direction until our parent is in direction we want to go.
	 */
	if (RB_SENTINEL_P(self->rb_nodes[direction])) {
		while (!RB_ROOT_P(rbt, self)) {
			if (other == (unsigned int)RB_POSITION(self))
				return RB_FATHER(self);
			self = RB_FATHER(self);
		}
		return NULL;
	}

	/*
	 * Advance down one in current direction and go down as far as possible
	 * in the opposite direction.
	 */
	self = self->rb_nodes[direction];
	while (!RB_SENTINEL_P(self->rb_nodes[other]))
		self = self->rb_nodes[other];
	return self;
}