{
	case 16: aes_key_len = 128; break;
	case 24: aes_key_len = 192; break;
	case 32: aes_key_len = 256; break;
	default: return -1;
	}