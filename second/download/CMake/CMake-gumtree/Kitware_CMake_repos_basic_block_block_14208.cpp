{
			case 'j': u = va_arg(ap, uintmax_t); break;
			case 'l': u = va_arg(ap, unsigned long); break;
			case 'z': u = va_arg(ap, size_t); break;
			default:  u = va_arg(ap, unsigned int); break;
			}