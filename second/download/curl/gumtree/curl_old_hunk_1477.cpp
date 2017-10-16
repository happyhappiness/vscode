  bar->width = scr_size[0] - 1;
#endif

  bar->out = config->errors;
}

void free_config_fields(struct Configurable *config)
{
  if(config->random_file)
    free(config->random_file);
  if(config->egd_file)
    free(config->egd_file);
