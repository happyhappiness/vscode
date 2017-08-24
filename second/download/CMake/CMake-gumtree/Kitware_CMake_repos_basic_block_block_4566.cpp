{
    data = body(ctx, data, size & ~(unsigned long)0x3f);
    size &= 0x3f;
  }