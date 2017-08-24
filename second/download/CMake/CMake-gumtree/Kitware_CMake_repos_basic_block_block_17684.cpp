(zip->encryption_type) {
		case ENCRYPTION_TRADITIONAL:
		case ENCRYPTION_WINZIP_AES128:
		case ENCRYPTION_WINZIP_AES256:
			zip->entry_flags |= ZIP_ENTRY_FLAG_ENCRYPTED;
			zip->entry_encryption = zip->encryption_type;
			break;
		default:
			break;
		}