(buffer == NULL || nLeftOver > bufferLim - buffer) {
        /* avoid _signed_ integer overflow */
        char *temp = NULL;
        const int bytesToAllocate = (int)((unsigned)len * 2U);
        if (bytesToAllocate > 0) {
          temp = (buffer == NULL
                ? (char *)MALLOC(bytesToAllocate)
                : (char *)REALLOC(buffer, bytesToAllocate));
        }
        if (temp == NULL) {
          errorCode = XML_ERROR_NO_MEMORY;
          eventPtr = eventEndPtr = NULL;
          processor = errorProcessor;
          return XML_STATUS_ERROR;
        }
        buffer = temp;
        bufferLim = buffer + bytesToAllocate;
      }