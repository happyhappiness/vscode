static void unload_file(gnutls_datum_t data)
{
  free(data.data);
}