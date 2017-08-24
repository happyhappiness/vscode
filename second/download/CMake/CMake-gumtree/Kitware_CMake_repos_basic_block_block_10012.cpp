(i = 0; i < MAX_OVERLAPPED; i++) {
		if (t->ol[i].buff)
			VirtualFree(t->ol[i].buff, 0, MEM_RELEASE);
		CloseHandle(t->ol[i].ol.hEvent);
	}