static int ir_shutdown (void)
{
  if ((rth.fd != 0) || (rth.seq != 0) || (rth.dump != 0))
  {
    rtnl_close(&rth);
    memset (&rth, '\0', sizeof (rth));
  }
  
  return (0);
}