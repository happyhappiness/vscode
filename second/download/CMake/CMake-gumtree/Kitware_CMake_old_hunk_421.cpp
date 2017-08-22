{
  int i, j, codebits = 0, symbolsleft = numsymbols;

  if (new_node(code) < 0) {
    archive_set_error(&a->archive, ENOMEM,
                      "Unable to allocate memory for node data.");
