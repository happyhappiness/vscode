{
			if (value >= 0)
				displacement = value - cp;
			else
				displacement = value + ds->translation_size;
			archive_le32enc(&b[1], (uint32_t)displacement);
		}