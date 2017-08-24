(i = 0; i < PVD_reserved4_size; ++i)
		if (h[PVD_reserved4_offset + i] != 0
		    && h[PVD_reserved4_offset + i] != 0x20)
			return (0);