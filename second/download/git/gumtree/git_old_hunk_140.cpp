	}
	CloseHandle(h);

	errno = EINVAL;
	return -1;
}
