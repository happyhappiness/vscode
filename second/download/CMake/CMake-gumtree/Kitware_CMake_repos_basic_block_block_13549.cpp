(p[3] == 'P') { p += 3; }
			else if (p[3] == 'K') { p += 2; }
			else if (p[3] == '\007') { p += 1; }
			else if (p[3] == '\010' && p[2] == '\007'
			    && p[1] == 'K' && p[0] == 'P') {
				if (zip->hctx_valid)
					p -= AUTH_CODE_SIZE;
				break;
			} else { p += 4; }