{
        int keep = (int)(bufferPtr - buffer);
        if (keep > XML_CONTEXT_BYTES)
          keep = XML_CONTEXT_BYTES;
        memcpy(newBuf, &bufferPtr[-keep], bufferEnd - bufferPtr + keep);
        FREE(buffer);
        buffer = newBuf;
        bufferEnd = buffer + (bufferEnd - bufferPtr) + keep;
        bufferPtr = buffer + keep;
      }