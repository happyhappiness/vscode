{
			case VERBATIM_BLOCK:
			case ALIGNED_OFFSET_BLOCK:
			case UNCOMPRESSED_BLOCK:
				break;
			default:
				goto failed;/* Invalid */
			}