{
		bitptn[i] = ptn;
		weight[i] = w;
		if (hf->freq[i]) {
			ptn += hf->freq[i] * w;
			maxbits = i;
		}
	}