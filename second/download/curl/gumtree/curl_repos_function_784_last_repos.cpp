int main(int argc, char **argv)
{
  int ii;
  FILE *infile;
  uint8_t *buffer = NULL;
  size_t buffer_len;

  for(ii = 1; ii < argc; ii++) {
    /* Try and open the file. */
    infile = fopen(argv[ii], "rb");
    if(infile) {
      printf("[%s] Open succeeded! \n", argv[ii]);

      /* Get the length of the file. */
      fseek(infile, 0L, SEEK_END);
      buffer_len = ftell(infile);

      /* Reset the file indicator to the beginning of the file. */
      fseek(infile, 0L, SEEK_SET);

      /* Allocate a buffer for the file contents. */
      buffer = (uint8_t *)calloc(buffer_len, sizeof(uint8_t));
      if(buffer) {
        /* Read all the text from the file into the buffer. */
        fread(buffer, sizeof(uint8_t), buffer_len, infile);
        printf("[%s] Read %zu bytes, calling fuzzer\n", argv[ii], buffer_len);

        /* Call the fuzzer with the data. */
        LLVMFuzzerTestOneInput(buffer, buffer_len);

        printf("[%s] Fuzzing complete\n", argv[ii]);

        /* Free the buffer as it's no longer needed. */
        free(buffer);
        buffer = NULL;
      }
      else
      {
        fprintf(stderr,
                "[%s] Failed to allocate %zu bytes \n",
                argv[ii],
                buffer_len);
      }

      /* Close the file as it's no longer needed. */
      fclose(infile);
      infile = NULL;
    }
    else
    {
      /* Failed to open the file. Maybe wrong name or wrong permissions? */
      fprintf(stderr, "[%s] Open failed. \n", argv[ii]);
    }
  }
}