{
			w *= w;
			bit_count <<= 1;

			while (w >= (UINT32_C(1) << 16)) {
				w >>= 1;
				++bit_count;
			}
		}