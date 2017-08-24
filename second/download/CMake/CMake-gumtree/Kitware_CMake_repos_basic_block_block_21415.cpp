(r) {
      case ERROR_BUFFER_OVERFLOW:
        /* This happens when win_address_buf is NULL or too small to hold */
        /* all adapters. */
        win_address_buf = uv__malloc(win_address_buf_size);
        if (win_address_buf == NULL)
          return UV_ENOMEM;

        continue;

      case ERROR_NO_DATA: {
        /* No adapters were found. */
        uv_address_buf = uv__malloc(1);
        if (uv_address_buf == NULL)
          return UV_ENOMEM;

        *count_ptr = 0;
        *addresses_ptr = uv_address_buf;

        return 0;
      }

      case ERROR_ADDRESS_NOT_ASSOCIATED:
        return UV_EAGAIN;

      case ERROR_INVALID_PARAMETER:
        /* MSDN says:
         *   "This error is returned for any of the following conditions: the
         *   SizePointer parameter is NULL, the Address parameter is not
         *   AF_INET, AF_INET6, or AF_UNSPEC, or the address information for
         *   the parameters requested is greater than ULONG_MAX."
         * Since the first two conditions are not met, it must be that the
         * adapter data is too big.
         */
        return UV_ENOBUFS;

      default:
        /* Other (unspecified) errors can happen, but we don't have any */
        /* special meaning for them. */
        assert(r != ERROR_SUCCESS);
        return uv_translate_sys_error(r);
    }