{
		/* copy aligned memory block as 64-bit integers */
		const uint64_t* src = (const uint64_t*)from;
		const uint64_t* end = (const uint64_t*)((const char*)src + length);
		uint64_t* dst = (uint64_t*)to;
		while (src < end) *(dst++) = bswap_64( *(src++) );
	}