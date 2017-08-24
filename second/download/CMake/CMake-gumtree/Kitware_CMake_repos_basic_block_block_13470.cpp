((bitmap_last & 0x80) != 0
			    && datasize >= 1) {
				bitmap_last = p[offset];
				offset += 1;
				datasize -= 1;
			}