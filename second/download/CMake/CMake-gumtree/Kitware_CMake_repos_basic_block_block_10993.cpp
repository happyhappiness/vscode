(i < 4) {
				/*
				 * Save odd bytes which we could not add into
				 * the output buffer because of out of space.
				 */
				zip->odd_bcj_size = 4 -i;
				for (; i < 4; i++) {
					j = i - 4 + (unsigned)zip->odd_bcj_size;
					zip->odd_bcj[j] = out[i];
				}
				break;
			}