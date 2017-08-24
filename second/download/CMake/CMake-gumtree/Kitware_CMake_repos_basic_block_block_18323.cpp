{
				uint32_t i;

				if (is_encoder)
					dest = src + (now_pos + (uint32_t)(
							buffer_pos) + 5);
				else
					dest = src - (now_pos + (uint32_t)(
							buffer_pos) + 5);

				if (prev_mask == 0)
					break;

				i = MASK_TO_BIT_NUMBER[prev_mask >> 1];

				b = (uint8_t)(dest >> (24 - i * 8));

				if (!Test86MSByte(b))
					break;

				src = dest ^ ((1u << (32 - i * 8)) - 1);
			}