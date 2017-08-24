(r == 0) {
			t->flags &= ~onWorkingDir;
			t->flags |= onInitialDir;
		}