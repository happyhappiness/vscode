{
	case METHOD_LZO1X_1:
		data->work_buffer_size = LZO1X_1_MEM_COMPRESS; break;
	case METHOD_LZO1X_1_15:
		data->work_buffer_size = LZO1X_1_15_MEM_COMPRESS; break;
	case METHOD_LZO1X_999:
		data->work_buffer_size = LZO1X_999_MEM_COMPRESS; break;
	}