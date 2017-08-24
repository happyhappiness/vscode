(Test86MSByte(p[4])) {
			uint32_t src = ((uint32_t)p[4] << 24) |
				((uint32_t)p[3] << 16) | ((uint32_t)p[2] << 8) |
				((uint32_t)p[1]);
			uint32_t dest;
			for (;;) {
				uint8_t b;
				int b_index;

				dest = src - (ip + (uint32_t)bufferPos);
				if (prevMask == 0)
					break;
				b_index = kMaskToBitNumber[prevMask] * 8;
				b = (uint8_t)(dest >> (24 - b_index));
				if (!Test86MSByte(b))
					break;
				src = dest ^ ((1 << (32 - b_index)) - 1);
			}
			p[4] = (uint8_t)(~(((dest >> 24) & 1) - 1));
			p[3] = (uint8_t)(dest >> 16);
			p[2] = (uint8_t)(dest >> 8);
			p[1] = (uint8_t)dest;
			bufferPos += 5;
		} else {
			prevMask = ((prevMask << 1) & 0x7) | 1;
			bufferPos++;
		}