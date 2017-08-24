(i = tail - 22; i > 0;) {
		switch (p[i]) {
		case 'P':
			if (memcmp(p + i, "PK\005\006", 4) == 0) {
				int ret = read_eocd(zip, p + i,
				    current_offset + i);
				if (ret > 0) {
					/* Zip64 EOCD locator precedes
					 * regular EOCD if present. */
					if (i >= 20
					    && memcmp(p + i - 20, "PK\006\007", 4) == 0) {
						read_zip64_eocd(a, zip, p + i - 20);
					}
					return (ret);
				}
			}
			i -= 4;
			break;
		case 'K': i -= 1; break;
		case 005: i -= 2; break;
		case 006: i -= 3; break;
		default: i -= 4; break;
		}
	}