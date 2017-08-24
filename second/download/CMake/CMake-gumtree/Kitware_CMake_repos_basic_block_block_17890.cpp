{
		if (pos == 64) {
			process(check);
			pos = 0;
		}

		check->buffer.u8[pos++] = 0x00;
	}