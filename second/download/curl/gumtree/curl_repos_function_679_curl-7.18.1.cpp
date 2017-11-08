void Curl_freeset(struct SessionHandle * data)
{
  /* Free all dynamic strings stored in the data->set substructure. */
  enum dupstring i;
  for(i=(enum dupstring)0; i < STRING_LAST; i++)
    Curl_safefree(data->set.str[i]);
}