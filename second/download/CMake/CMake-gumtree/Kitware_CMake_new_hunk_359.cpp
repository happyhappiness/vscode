  printf("md5sum 1: expected [%s]\n"
         "               got [%s]\n",
         testMD5output1, md5out);
  return (strcmp(md5out, testMD5output1) != 0) ? 1 : 0;
}

static int testMD5_2(kwsysMD5* md5)
