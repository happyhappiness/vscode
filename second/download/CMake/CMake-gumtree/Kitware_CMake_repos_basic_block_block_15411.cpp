(i = 1; i < (int)sizeof(numdata); i++) {
		if (val < mask) {
			numdata[0] |= (uint8_t)val;
			break;
		}
		numdata[i] = (uint8_t)val;
		val >>= 8;
		numdata[0] |= mask;
		mask >>= 1;
	}