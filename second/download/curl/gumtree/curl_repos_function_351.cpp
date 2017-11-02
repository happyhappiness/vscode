char *
curl_form_long_value(long value)

{
  /* ILE/RPG cannot cast an integer to a pointer. This procedure does it. */

  return (char *) value;
}