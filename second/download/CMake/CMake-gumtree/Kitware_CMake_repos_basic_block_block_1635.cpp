{
  /* Append a null-terminator to the argument string.  */
  if (!kwsysSystem__AppendByte(arg_local, arg_begin, arg_end, arg_size,
                               '\0')) {
    return 0;
  }

  /* Allocate space for the argument pointer.  */
  if ((*end - *begin) >= *size) {
    kwsysSystem_ptrdiff_t length = *end - *begin;
    char** newPointers = (char**)malloc((size_t)(*size) * 2 * sizeof(char*));
    if (!newPointers) {
      return 0;
    }
    memcpy(newPointers, *begin, (size_t)(length) * sizeof(char*));
    if (*begin != local) {
      free(*begin);
    }
    *begin = newPointers;
    *end = *begin + length;
    *size *= 2;
  }

  /* Allocate space for the argument string.  */
  **end = (char*)malloc((size_t)(*arg_end - *arg_begin));
  if (!**end) {
    return 0;
  }

  /* Store the argument in the command array.  */
  memcpy(**end, *arg_begin, (size_t)(*arg_end - *arg_begin));
  ++(*end);

  /* Reset the argument to be empty.  */
  *arg_end = *arg_begin;

  return 1;
}