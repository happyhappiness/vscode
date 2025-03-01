{
	case 0:
		/*
		 * Note: Self-Extraction program has 'MSCF' string in their
		 * program. If we were finding 'MSCF' string only, we got
		 * wrong place for Cabinet header, thus, we have to check
		 * following four bytes which are reserved and must be set
		 * to zero.
		 */
		if (memcmp(p, "MSCF\0\0\0\0", 8) == 0)
			return 0;
		return 5;
	case 'F': return 1;
	case 'C': return 2;
	case 'S': return 3;
	case 'M': return 4;
	default:  return 5;
	}