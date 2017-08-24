{
			t->stack->flags &= ~needsOpen;
			r = tree_dir_next_windows(t, L"*");
			if (r == 0)
				continue;
			return (r);
		}