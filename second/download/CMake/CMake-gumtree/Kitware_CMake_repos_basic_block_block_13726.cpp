(p[i + 3]) {
			case 'P': i += 3; break;
			case 'K': i += 2; break;
			case 001: i += 1; break;
			case 002:
				if (memcmp(p + i, "PK\001\002", 4) == 0) {
					p += i;
					found = 1;
				} else
					i += 4;
				break;
			case 005: i += 1; break;
			case 006:
				if (memcmp(p + i, "PK\005\006", 4) == 0) {
					p += i;
					found = 1;
				} else if (memcmp(p + i, "PK\006\006", 4) == 0) {
					p += i;
					found = 1;
				} else
					i += 1;
				break;
			default: i += 4; break;
			}