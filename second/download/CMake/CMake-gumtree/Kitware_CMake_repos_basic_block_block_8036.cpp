{
        XML_Char buf[XML_ENCODE_MAX];
        int i;
        int n = XmlCharRefNumber(enc, ptr);
        if (n < 0) {
          if (enc == encoding)
            eventPtr = ptr;
          return XML_ERROR_BAD_CHAR_REF;
        }
        if (!isCdata
            && n == 0x20 /* space */
            && (poolLength(pool) == 0 || poolLastChar(pool) == 0x20))
          break;
        n = XmlEncode(n, (ICHAR *)buf);
        if (!n) {
          if (enc == encoding)
            eventPtr = ptr;
          return XML_ERROR_BAD_CHAR_REF;
        }
        for (i = 0; i < n; i++) {
          if (!poolAppendChar(pool, buf[i]))
            return XML_ERROR_NO_MEMORY;
        }
      }