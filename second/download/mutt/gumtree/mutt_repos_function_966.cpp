void pgp_release_packet (void)
{
  plen = 0;
  FREE (&pbuf);
}