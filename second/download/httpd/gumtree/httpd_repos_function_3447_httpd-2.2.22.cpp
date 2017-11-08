void _NonAppStop( void )
{
  if (getenv("_IN_NETWARE_BASH_") == NULL) {
    printf("\r\n<Press any key to close screen> ");
    getcharacter();
  }
}