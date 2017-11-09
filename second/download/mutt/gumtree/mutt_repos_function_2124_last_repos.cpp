static int compare_names(struct folder_file *a, struct folder_file *b) 
{
  return mutt_strcmp(a->name, b->name);
}