{
		states &= ~lowbit;		/* Clear the low bit. */
		strcat(buff, state_name(lowbit));
		if (states != 0)
			strcat(buff, "/");
	}