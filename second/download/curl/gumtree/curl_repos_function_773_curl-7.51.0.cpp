int metalink_check_hash(struct GlobalConfig *config,
                        metalinkfile *mlfile,
                        const char *filename)
{
  int rv;
  fprintf(config->errors, "Metalink: validating (%s)...\n", filename);
  if(mlfile->checksum == NULL) {
    fprintf(config->errors,
            "Metalink: validating (%s) FAILED (digest missing)\n", filename);
    return -2;
  }
  rv = check_hash(filename, mlfile->checksum->digest_def,
                  mlfile->checksum->digest, config->errors);
  return rv;
}