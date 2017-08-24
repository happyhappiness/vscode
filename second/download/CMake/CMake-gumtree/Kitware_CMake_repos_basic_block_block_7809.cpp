(i == sizeof(encodingBuf) - 1
          || (protocolEncodingName[i] & ~0x7f) != 0) {
        encodingBuf[0] = '\0';
        break;
      }