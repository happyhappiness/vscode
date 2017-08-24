{
			case 'j': s = va_arg(ap, intmax_t); break;
			case 'l': s = va_arg(ap, long); break;
			case 'z': s = va_arg(ap, ssize_t); break;
			default:  s = va_arg(ap, int); break;
			}