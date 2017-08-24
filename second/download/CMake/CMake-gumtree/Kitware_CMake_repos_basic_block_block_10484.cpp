{
	case 0x00001000:/* lzma of LZMA SDK option -d12. */
	case 0x00002000:/* lzma of LZMA SDK option -d13. */
	case 0x00004000:/* lzma of LZMA SDK option -d14. */
	case 0x00008000:/* lzma of LZMA SDK option -d15. */
	case 0x00010000:/* lzma of XZ Utils option -0 and -1.
			 * lzma of LZMA SDK option -d16. */
	case 0x00020000:/* lzma of LZMA SDK option -d17. */
	case 0x00040000:/* lzma of LZMA SDK option -d18. */
	case 0x00080000:/* lzma of XZ Utils option -2.
			 * lzma of LZMA SDK option -d19. */
	case 0x00100000:/* lzma of XZ Utils option -3.
			 * lzma of LZMA SDK option -d20. */
	case 0x00200000:/* lzma of XZ Utils option -4.
			 * lzma of LZMA SDK option -d21. */
	case 0x00400000:/* lzma of XZ Utils option -5.
			 * lzma of LZMA SDK option -d22. */
	case 0x00800000:/* lzma of XZ Utils option -6.
			 * lzma of LZMA SDK option -d23. */
	case 0x01000000:/* lzma of XZ Utils option -7.
			 * lzma of LZMA SDK option -d24. */
	case 0x02000000:/* lzma of XZ Utils option -8.
			 * lzma of LZMA SDK option -d25. */
	case 0x04000000:/* lzma of XZ Utils option -9.
			 * lzma of LZMA SDK option -d26. */
	case 0x08000000:/* lzma of LZMA SDK option -d27. */
		bits_checked += 32;
		break;
	default:
		/* If a memory usage for encoding was not enough on
		 * the platform where LZMA stream was made, lzma of
		 * XZ Utils automatically decreased the dictionary
		 * size to enough memory for encoding by 1Mi bytes
		 * (1 << 20).*/
		if (dicsize <= 0x03F00000 && dicsize >= 0x00300000 &&
		    (dicsize & ((1 << 20)-1)) == 0 &&
		    bits_checked == 8 + 64) {
			bits_checked += 32;
			break;
		}
		/* Otherwise dictionary size is unlikely. But it is
		 * possible that someone makes lzma stream with
		 * liblzma/LZMA SDK in one's dictionary size. */
		return (0);
	}