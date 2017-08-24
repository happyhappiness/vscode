{
		in[i] = i;

		if (siphash24(in, i, &k) != SIP_U8TO64_LE(vectors[i]))
			return 0;
	}