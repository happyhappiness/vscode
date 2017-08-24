(key_len) {
	case 16: ctx->type = EVP_aes_128_ecb(); break;
	case 24: ctx->type = EVP_aes_192_ecb(); break;
	case 32: ctx->type = EVP_aes_256_ecb(); break;
	default: ctx->type = NULL; return -1;
	}