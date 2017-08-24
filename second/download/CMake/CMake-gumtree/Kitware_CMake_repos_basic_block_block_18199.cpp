(coder->need_state_reset)
			coder->buf[pos] = 0x80 + (1 << 5);
		else
			coder->buf[pos] = 0x80