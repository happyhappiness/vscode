static void main_free(struct GlobalConfig *config)
{
  /* Cleanup the easy handle */
  curl_easy_cleanup(config->easy);
  config->easy = NULL;

  /* Main cleanup */
  curl_global_cleanup();
  convert_cleanup();
  metalink_cleanup();
#ifdef USE_NSS
  if(PR_Initialized()) {
    /* prevent valgrind from reporting still reachable mem from NSRP arenas */
    PL_ArenaFinish();
    /* prevent valgrind from reporting possibly lost memory (fd cache, ...) */
    PR_Cleanup();
  }
#endif
  free_config_fields(config);

  /* Free the config structures */
  config_free(config->last);
  config->first = NULL;
  config->last = NULL;
}