{
#if defined(KWIML_ABI_ENDIAN_ID)
  int expect;
  union { short s; unsigned char c[sizeof(short)]; } x;
  x.s = 1;
  expect = (x.c[0] == 1 ?
            KWIML_ABI_ENDIAN_ID_LITTLE : KWIML_ABI_ENDIAN_ID_BIG);
  printf(LANG "KWIML_ABI_ENDIAN_ID: expected [%d], got [%d]",
         expect, KWIML_ABI_ENDIAN_ID);
  if(KWIML_ABI_ENDIAN_ID == expect)
    {
    printf(", PASSED\n");
    }
  else
    {
    printf(", FAILED\n");
    result = 0;
    }
#else
  printf(LANG "KWIML_ABI_ENDIAN_ID: unknown, FAILED\n");
  result = 0;
#endif
  }