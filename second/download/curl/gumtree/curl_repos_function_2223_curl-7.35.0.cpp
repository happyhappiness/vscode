static void unload_file(gnutls_datum data) {
  free(data.data);
}