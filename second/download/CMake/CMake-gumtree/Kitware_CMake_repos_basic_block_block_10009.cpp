{
		FindClose(t->d);
		t->d = INVALID_HANDLE_VALUE;
		t->findData = NULL;
	}