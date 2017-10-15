}

char*
print_download_status(char* first, char* last, core::Download* d) {
  if (d->is_active())
    ;
  else if (rpc::call_command_d_value("get_d_hashing", d) != 0)
    first = print_buffer(first, last, "Hashing: ");
  else if (!d->is_active())
    first = print_buffer(first, last, "Inactive: ");

  if (d->is_hash_checking()) {
    first = print_buffer(first, last, "Checking hash [%2i%%]",
