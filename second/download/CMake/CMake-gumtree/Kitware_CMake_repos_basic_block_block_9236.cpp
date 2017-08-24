{
		self = rbt->rbt_root;
		if (RB_SENTINEL_P(self))
			return NULL;
		while (!RB_SENTINEL_P(self->rb_nodes[direction]))
			self = self->rb_nodes[direction];
		return self;
	}