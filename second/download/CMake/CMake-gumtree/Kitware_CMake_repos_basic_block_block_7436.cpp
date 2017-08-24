{
	case 7: b |= (uint64_t)H->buf[6] << 48;
	case 6: b |= (uint64_t)H->buf[5] << 40;
	case 5: b |= (uint64_t)H->buf[4] << 32;
	case 4: b |= (uint64_t)H->buf[3] << 24;
	case 3: b |= (uint64_t)H->buf[2] << 16;
	case 2: b |= (uint64_t)H->buf[1] << 8;
	case 1: b |= (uint64_t)H->buf[0] << 0;
	case 0: break;
	}