{
				uint16_t *pc;

				cnt -= 8;
				pc = &p[cnt];
				pc[0] = (uint16_t)i;
				pc[1] = (uint16_t)i;
				pc[2] = (uint16_t)i;
				pc[3] = (uint16_t)i;
				pc[4] = (uint16_t)i;
				pc[5] = (uint16_t)i;
				pc[6] = (uint16_t)i;
				pc[7] = (uint16_t)i;
				if (cnt > 7) {
					cnt -= 8;
					memcpy(&p[cnt], pc,
						8 * sizeof(uint16_t));
					pc = &p[cnt];
					while (cnt > 15) {
						cnt -= 16;
						memcpy(&p[cnt], pc,
							16 * sizeof(uint16_t));
					}
				}
				if (cnt)
					memcpy(p, pc, cnt * sizeof(uint16_t));
			}