{
  if (!filename || !signature) {
    return false;
  }

  FILE* fp = Fopen(filename, "rb");
  if (!fp) {
    return false;
  }

  fseek(fp, offset, SEEK_SET);

  bool res = false;
  size_t signature_len = strlen(signature);
  char* buffer = new char[signature_len];

  if (fread(buffer, 1, signature_len, fp) == signature_len) {
    res = (!strncmp(buffer, signature, signature_len) ? true : false);
  }

  delete[] buffer;

  fclose(fp);
  return res;
}