{
		if (--arc4_count <= 0)
			arc4_stir();
		buf[n] = arc4_getbyte();
	}