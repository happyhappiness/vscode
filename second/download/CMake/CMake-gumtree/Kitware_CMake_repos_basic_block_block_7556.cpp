{
        int offset = (int)(bufferPtr - buffer) - keep;
        memmove(buffer, &buffer[offset], bufferEnd - bufferPtr + keep);
        bufferEnd -= offset;
        bufferPtr -= offset;
      }