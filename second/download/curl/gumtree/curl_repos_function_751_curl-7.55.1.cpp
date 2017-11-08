struct multi_files *AddMultiFiles(const char *file_name,
                                  const char *type_name,
                                  const char *show_filename,
                                  struct multi_files **multi_first,
                                  struct multi_files **multi_last)
{
  struct multi_files *multi;
  struct multi_files *multi_type;
  struct multi_files *multi_name;

  multi = calloc(1, sizeof(struct multi_files));
  if(multi) {
    multi->form.option = CURLFORM_FILE;
    multi->form.value = file_name;
    AppendNode(multi_first, multi_last, multi);
  }
  else {
    FreeMultiInfo(multi_first, multi_last);
    return NULL;
  }

  if(type_name) {
    multi_type = calloc(1, sizeof(struct multi_files));
    if(multi_type) {
      multi_type->form.option = CURLFORM_CONTENTTYPE;
      multi_type->form.value = type_name;
      AppendNode(multi_first, multi_last, multi_type);
    }
    else {
      FreeMultiInfo(multi_first, multi_last);
      return NULL;
    }
  }

  if(show_filename) {
    multi_name = calloc(1, sizeof(struct multi_files));
    if(multi_name) {
      multi_name->form.option = CURLFORM_FILENAME;
      multi_name->form.value = show_filename;
      AppendNode(multi_first, multi_last, multi_name);
    }
    else {
      FreeMultiInfo(multi_first, multi_last);
      return NULL;
    }
  }

  return *multi_last;
}