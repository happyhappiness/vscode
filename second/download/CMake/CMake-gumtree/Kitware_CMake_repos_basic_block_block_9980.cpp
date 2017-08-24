{
			/* Top item on stack is dead. */
			tree_pop(t);
			t->flags &= ~hasLstat;
			t->flags &= ~hasStat;
		}