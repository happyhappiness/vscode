{
		RB_SET_FATHER(new_child->rb_nodes[which], new_child);
		RB_SET_POSITION(new_child->rb_nodes[which], which);
	}