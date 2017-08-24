{
			t->stack->flags &= ~needsOpen;
			r = tree_dir_next_posix(t);
			if (r == 0)
				continue;
			return (r);
		}