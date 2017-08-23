  printf("md5sum 2: expected [%s]\n"
         "               got [%s]\n",
         testMD5output2, md5out);
  return (strcmp(md5out, testMD5output2) != 0)? 1:0;
}

int testEncode(int argc, char* argv[])
