{
			case 'o': append_uint(as, u, 8); break;
			case 'u': append_uint(as, u, 10); break;
			default: append_uint(as, u, 16); break;
			}