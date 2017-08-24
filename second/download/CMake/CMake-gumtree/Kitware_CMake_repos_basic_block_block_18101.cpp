{
		buffer[i] += coder->history[(distance + coder->pos) & 0xFF];
		coder->history[coder->pos-- & 0xFF] = buffer[i];
	}