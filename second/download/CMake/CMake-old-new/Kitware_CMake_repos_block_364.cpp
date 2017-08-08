{
			case ENOTSUP:
			case ENOSYS:
#if ENOTSUP != EOPNOTSUPP
			case EOPNOTSUPP:
#endif
				/*
				 * if lchmod is defined but the platform
				 * doesn't support it, silently ignore
				 * error
				 */
				break;
			default:
				archive_set_error(&a->archive, errno,
				    "Can't set permissions to 0%o", (int)mode);
				r = ARCHIVE_WARN;
			}