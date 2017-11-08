void clean_metalink(struct Configurable *config)
{
  while(config->metalinkfile_list) {
    metalinkfile *mlfile = config->metalinkfile_list;
    config->metalinkfile_list = config->metalinkfile_list->next;
    delete_metalinkfile(mlfile);
  }
  config->metalinkfile_last = 0;
}