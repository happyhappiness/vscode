{
	case 0x6601:/* DES */
	case 0x6602:/* RC2 */
	case 0x6603:/* 3DES 168 */
	case 0x6609:/* 3DES 112 */
	case 0x660E:/* AES 128 */
	case 0x660F:/* AES 192 */
	case 0x6610:/* AES 256 */
	case 0x6702:/* RC2 (version >= 5.2) */
	case 0x6720:/* Blowfish */
	case 0x6721:/* Twofish */
	case 0x6801:/* RC4 */
		/* Supported encryption algorithm. */
		break;
	default:
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Unknown encryption algorithm: %u", zip->alg_id);
		return (ARCHIVE_FAILED);
	}