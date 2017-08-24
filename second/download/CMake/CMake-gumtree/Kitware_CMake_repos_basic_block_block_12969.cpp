{
		case 4: d[2] = v & 0xff;
			/* FALLTHROUGH */
		case 3: d[1] = (v >> 8) & 0xff;
			/* FALLTHROUGH */
		case 2: d[0] = (v >> 16) & 0xff;
			break;
		case 1: /* this is invalid! */
			break;
		}