{
		case LZMA_MODE_FAST:
			coder->fast_mode = true;
			break;

		case LZMA_MODE_NORMAL: {
			coder->fast_mode = false;

			// Set dist_table_size.
			// Round the dictionary size up to next 2^n.
			while ((UINT32_C(1) << log_size) < options->dict_size)
				++log_size;

			coder->dist_table_size = log_size * 2;

			// Length encoders' price table size
			coder->match_len_encoder.table_size
				= options->nice_len + 1 - MATCH_LEN_MIN;
			coder->rep_len_encoder.table_size
				= options->nice_len + 1 - MATCH_LEN_MIN;
			break;
		}

		default:
			return LZMA_OPTIONS_ERROR;
	}