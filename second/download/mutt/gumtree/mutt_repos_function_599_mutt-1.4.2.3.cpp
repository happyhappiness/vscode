void pgp_release_packet (void)
{
  plen = 0;
  safe_free ((void **) &pbuf);
}