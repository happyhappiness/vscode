{
	case 0: break;
	case 1:
		v = (((int)s[0] << 16) & 0xff0000);
		*d++ = digits[(v >> 18) & 0x3f];
		*d++ = digits[(v >> 12) & 0x3f];
		break;
	case 2:
		v = (((int)s[0] << 16) & 0xff0000)
		    | (((int)s[1] << 8) & 0xff00);
		*d++ = digits[(v >> 18) & 0x3f];
		*d++ = digits[(v >> 12) & 0x3f];
		*d++ = digits[(v >> 6) & 0x3f];
		break;
	}