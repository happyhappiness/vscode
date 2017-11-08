void _NonAppStop( void )
{
  if (getenv("_IN_NETWARE_BASH_") == NULL)
    pressanykey();
}