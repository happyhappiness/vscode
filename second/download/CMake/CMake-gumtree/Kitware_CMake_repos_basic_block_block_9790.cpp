{
			t->stack->symlink_parent_fd = t->working_dir_fd;
			t->openCount++;
			if (t->openCount > t->maxOpenCount)
				t->maxOpenCount = t->openCount;
		}