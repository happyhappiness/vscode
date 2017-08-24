{
    case 0:                       return 0;
    case WSATRY_AGAIN:            return UV_EAI_AGAIN;
    case WSAEINVAL:               return UV_EAI_BADFLAGS;
    case WSANO_RECOVERY:          return UV_EAI_FAIL;
    case WSAEAFNOSUPPORT:         return UV_EAI_FAMILY;
    case WSA_NOT_ENOUGH_MEMORY:   return UV_EAI_MEMORY;
    case WSAHOST_NOT_FOUND:       return UV_EAI_NONAME;
    case WSATYPE_NOT_FOUND:       return UV_EAI_SERVICE;
    case WSAESOCKTNOSUPPORT:      return UV_EAI_SOCKTYPE;
    default:                      return uv_translate_sys_error(sys_err);
  }