(len > ((XML_Size)-1) / 2 - parseEndByteIndex) {
       errorCode = XML_ERROR_NO_MEMORY;
       eventPtr = eventEndPtr = NULL;
       processor = errorProcessor;
       return XML_STATUS_ERROR;
    }