static int testMD5_1(kwsysMD5* md5)
{
  char md5out[33];
  kwsysMD5_Initialize(md5);
  kwsysMD5_Append(md5, testMD5input1, -1);
  kwsysMD5_FinalizeHex(md5, md5out);
  md5out[32] = 0;
  printf("md5sum 1: expected [%s]\n"
         "               got [%s]\n",
         testMD5output1, md5out);
  return (strcmp(md5out, testMD5output1) != 0) ? 1 : 0;
}