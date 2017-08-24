{
			case BZ_PARAM_ERROR:
				detail = "invalid setup parameter";
				break;
			case BZ_MEM_ERROR:
				err = ENOMEM;
				detail = "out of memory";
				break;
			case BZ_CONFIG_ERROR:
				detail = "mis-compiled library";
				break;
			}