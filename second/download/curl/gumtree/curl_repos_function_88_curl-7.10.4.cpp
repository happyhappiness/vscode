int main(int argc, char *argv[])
{
  int res;
  struct Configurable config;
  memset(&config, 0, sizeof(struct Configurable));
  
  res = operate(&config, argc, argv);
  free_config_fields(&config);

#ifdef	VMS
  if (res > 52) res = 53;		/* MAXMSG, porting helper */
  return (vms_cond[res]|vms_show);
#else
  return res;
#endif
}