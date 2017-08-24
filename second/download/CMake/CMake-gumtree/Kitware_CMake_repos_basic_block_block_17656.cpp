(zip->entry_encryption) {
			case ENCRYPTION_TRADITIONAL:
			case ENCRYPTION_WINZIP_AES128:
			case ENCRYPTION_WINZIP_AES256:
				if (version_needed < 20)
					version_needed = 20;
				break;
			default:
				break;
			}