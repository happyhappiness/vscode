{
		ctl->cur_len++;
		if (ctl->bp != NULL)
			ctl->bp[ctl->cur_len] = 0;
		padding = 1;
	}