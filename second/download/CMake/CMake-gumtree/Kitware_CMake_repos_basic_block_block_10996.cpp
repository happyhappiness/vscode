{
				uint8_t bb = buf0[inPos];
				outBuf[outPos++] = bb;
				if (IsJ(zip->bcj2_prevByte, bb)) {
					zip->bcj_state = 2;
					break;
				}
				inPos++;
				zip->bcj2_prevByte = bb;
				limit--;
			}