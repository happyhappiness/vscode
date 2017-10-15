
  return first;
}

char*
print_download_status(char* first, char* last, core::Download* d) {
  if (d->is_active())
    ;
  else if (d->variable_value("hashing") != 0)
    first = print_buffer(first, last, "Hashing: ");
  else if (!d->is_active())
    first = print_buffer(first, last, "Inactive: ");

  if (d->is_hash_checking()) {
    first = print_buffer(first, last, "Checking hash [%2i%%]",
                         (d->download()->chunks_hashed() * 100) / d->download()->chunks_total());

