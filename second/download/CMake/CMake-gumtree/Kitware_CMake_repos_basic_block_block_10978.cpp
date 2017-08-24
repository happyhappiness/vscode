{
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