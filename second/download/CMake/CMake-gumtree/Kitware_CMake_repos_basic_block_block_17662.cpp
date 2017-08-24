(zip->entry_encryption) {
			case ENCRYPTION_TRADITIONAL:
				additional_size = TRAD_HEADER_SIZE;
				version_needed = 20;
				break;
			case ENCRYPTION_WINZIP_AES128:
				additional_size = WINZIP_AES128_HEADER_SIZE
				    + AUTH_CODE_SIZE;
				version_needed = 20;
				break;
			case ENCRYPTION_WINZIP_AES256:
				additional_size = WINZIP_AES256_HEADER_SIZE
				    + AUTH_CODE_SIZE;
				version_needed = 20;
				break;
			default:
				break;
			}