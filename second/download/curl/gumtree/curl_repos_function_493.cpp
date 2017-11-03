static int test_unsigned_long_formatting(void)
{
  int i, j;
  int num_ulong_tests;
  int failed = 0;

#if (CURL_SIZEOF_LONG == 2)

  i=1; ul_test[i].num = 0xFFFFUL; ul_test[i].expected = "65535";
  i++; ul_test[i].num = 0xFF00UL; ul_test[i].expected = "65280";
  i++; ul_test[i].num = 0x00FFUL; ul_test[i].expected = "255";

  i++; ul_test[i].num = 0xF000UL; ul_test[i].expected = "61440";
  i++; ul_test[i].num = 0x0F00UL; ul_test[i].expected = "3840";
  i++; ul_test[i].num = 0x00F0UL; ul_test[i].expected = "240";
  i++; ul_test[i].num = 0x000FUL; ul_test[i].expected = "15";

  i++; ul_test[i].num = 0xC000UL; ul_test[i].expected = "49152";
  i++; ul_test[i].num = 0x0C00UL; ul_test[i].expected = "3072";
  i++; ul_test[i].num = 0x00C0UL; ul_test[i].expected = "192";
  i++; ul_test[i].num = 0x000CUL; ul_test[i].expected = "12";

  i++; ul_test[i].num = 0x0001UL; ul_test[i].expected = "1";
  i++; ul_test[i].num = 0x0000UL; ul_test[i].expected = "0";

  num_ulong_tests = i;

#elif (CURL_SIZEOF_LONG == 4)

  i=1; ul_test[i].num = 0xFFFFFFFFUL; ul_test[i].expected = "4294967295";
  i++; ul_test[i].num = 0xFFFF0000UL; ul_test[i].expected = "4294901760";
  i++; ul_test[i].num = 0x0000FFFFUL; ul_test[i].expected = "65535";

  i++; ul_test[i].num = 0xFF000000UL; ul_test[i].expected = "4278190080";
  i++; ul_test[i].num = 0x00FF0000UL; ul_test[i].expected = "16711680";
  i++; ul_test[i].num = 0x0000FF00UL; ul_test[i].expected = "65280";
  i++; ul_test[i].num = 0x000000FFUL; ul_test[i].expected = "255";

  i++; ul_test[i].num = 0xF0000000UL; ul_test[i].expected = "4026531840";
  i++; ul_test[i].num = 0x0F000000UL; ul_test[i].expected = "251658240";
  i++; ul_test[i].num = 0x00F00000UL; ul_test[i].expected = "15728640";
  i++; ul_test[i].num = 0x000F0000UL; ul_test[i].expected = "983040";
  i++; ul_test[i].num = 0x0000F000UL; ul_test[i].expected = "61440";
  i++; ul_test[i].num = 0x00000F00UL; ul_test[i].expected = "3840";
  i++; ul_test[i].num = 0x000000F0UL; ul_test[i].expected = "240";
  i++; ul_test[i].num = 0x0000000FUL; ul_test[i].expected = "15";

  i++; ul_test[i].num = 0xC0000000UL; ul_test[i].expected = "3221225472";
  i++; ul_test[i].num = 0x0C000000UL; ul_test[i].expected = "201326592";
  i++; ul_test[i].num = 0x00C00000UL; ul_test[i].expected = "12582912";
  i++; ul_test[i].num = 0x000C0000UL; ul_test[i].expected = "786432";
  i++; ul_test[i].num = 0x0000C000UL; ul_test[i].expected = "49152";
  i++; ul_test[i].num = 0x00000C00UL; ul_test[i].expected = "3072";
  i++; ul_test[i].num = 0x000000C0UL; ul_test[i].expected = "192";
  i++; ul_test[i].num = 0x0000000CUL; ul_test[i].expected = "12";

  i++; ul_test[i].num = 0x00000001UL; ul_test[i].expected = "1";
  i++; ul_test[i].num = 0x00000000UL; ul_test[i].expected = "0";

  num_ulong_tests = i;

#elif (CURL_SIZEOF_LONG == 8)

  i=1; ul_test[i].num = 0xFFFFFFFFFFFFFFFFUL; ul_test[i].expected = "18446744073709551615";
  i++; ul_test[i].num = 0xFFFFFFFF00000000UL; ul_test[i].expected = "18446744069414584320";
  i++; ul_test[i].num = 0x00000000FFFFFFFFUL; ul_test[i].expected = "4294967295";

  i++; ul_test[i].num = 0xFFFF000000000000UL; ul_test[i].expected = "18446462598732840960";
  i++; ul_test[i].num = 0x0000FFFF00000000UL; ul_test[i].expected = "281470681743360";
  i++; ul_test[i].num = 0x00000000FFFF0000UL; ul_test[i].expected = "4294901760";
  i++; ul_test[i].num = 0x000000000000FFFFUL; ul_test[i].expected = "65535";

  i++; ul_test[i].num = 0xFF00000000000000UL; ul_test[i].expected = "18374686479671623680";
  i++; ul_test[i].num = 0x00FF000000000000UL; ul_test[i].expected = "71776119061217280";
  i++; ul_test[i].num = 0x0000FF0000000000UL; ul_test[i].expected = "280375465082880";
  i++; ul_test[i].num = 0x000000FF00000000UL; ul_test[i].expected = "1095216660480";
  i++; ul_test[i].num = 0x00000000FF000000UL; ul_test[i].expected = "4278190080";
  i++; ul_test[i].num = 0x0000000000FF0000UL; ul_test[i].expected = "16711680";
  i++; ul_test[i].num = 0x000000000000FF00UL; ul_test[i].expected = "65280";
  i++; ul_test[i].num = 0x00000000000000FFUL; ul_test[i].expected = "255";

 