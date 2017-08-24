{
      /* The query requires a bigger buffer.  */
      int newBufferSize = self->BufferSize * 2;
      char* newBuffer = (char*)malloc(newBufferSize);
      if (newBuffer) {
        free(self->Buffer);
        self->Buffer = newBuffer;
        self->BufferSize = newBufferSize;
      } else {
        return 0;
      }
    }