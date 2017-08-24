{
  FILE *f;
  gnutls_datum_t loaded_file = { NULL, 0 };
  long filelen;
  void *ptr;

  f = fopen(file, "rb");
  if(!f)
    return loaded_file;
  if(fseek(f, 0, SEEK_END) != 0
     || (filelen = ftell(f)) < 0
     || fseek(f, 0, SEEK_SET) != 0
     || !(ptr = malloc((size_t)filelen)))
    goto out;
  if(fread(ptr, 1, (size_t)filelen, f) < (size_t)filelen) {
    free(ptr);
    goto out;
  }

  loaded_file.data = ptr;
  loaded_file.size = (unsigned int)filelen;
out:
  fclose(f);
  return loaded_file;
}