int test(char *URL)
{
  int errors = 0;
  (void)URL; /* not used */

#ifdef HAVE_SETLOCALE
  /*
   * The test makes assumptions about the numeric locale (specifically,
   * RADIXCHAR) so set it to a known working (and portable) one.
   */
  setlocale(LC_NUMERIC, "C");
#endif

  errors += test_weird_arguments();

  errors += test_unsigned_short_formatting();

  errors += test_signed_short_formatting();

  errors += test_unsigned_int_formatting();

  errors += test_signed_int_formatting();

  errors += test_unsigned_long_formatting();

  errors += test_signed_long_formatting();

  errors += test_curl_off_t_formatting();

  errors += test_string_formatting();

  errors += test_float_formatting();

  if(errors)
    return TEST_ERR_MAJOR_BAD;
  else
    return 0;
}