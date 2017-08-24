(zip->entry->aes_extra.strength) {
	case 1: salt_len = 8;  key_len = 16; break;
	case 2: salt_len = 12; key_len = 24; break;
	case 3: salt_len = 16; key_len = 32; break;
	default: goto corrupted;
	}