{
  unsigned char digest[16];
  char md5out[33];
  kwsysMD5_Initialize(md5);
  kwsysMD5_Append(md5, testMD5input2, testMD5input2len);
  kwsysMD5_Finalize(md5, digest);
  kwsysMD5_DigestToHex(digest, md5out);
  md5out[32] = 0;
  printf("md5sum 2: expected [%s]\n"
         "               got [%s]\n",
         testMD5output2, md5out);
  return (strcmp(md5out, testMD5output2) != 0)? 1:0;
}