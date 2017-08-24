{
	case 1:
		data->method = METHOD_LZO1X_1_15; data->level = 1; break;
	default:
	case 2: case 3: case 4: case 5: case 6:
		data->method = METHOD_LZO1X_1; data->level = 5; break;
	case 7:
		data->method = METHOD_LZO1X_999; data->level = 7; break;
	case 8:
		data->method = METHOD_LZO1X_999; data->level = 8; break;
	case 9:
		data->method = METHOD_LZO1X_999; data->level = 9; break;
	}