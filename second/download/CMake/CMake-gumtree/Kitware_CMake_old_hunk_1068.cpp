int check_defines_CXX()
{
  int result = 1;
#ifndef PREPROCESS_VS6
  if(strcmp(FILE_STRING, STRING_VALUE) != 0)
    {
    fprintf(stderr,
