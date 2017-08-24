{
        free(self->Buffer);
        self->Buffer = newBuffer;
        self->BufferSize = newBufferSize;
      }