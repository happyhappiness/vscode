{
		output_byte(f, ocode & 0xff);
		ocode >>= 8;
		bits -= 8;
	}