(flag & SCONV_TO_UTF8)
			flag |= SCONV_NORMALIZATION_D;
		else
#endif
			flag |= SCONV_NORMALIZATION_C