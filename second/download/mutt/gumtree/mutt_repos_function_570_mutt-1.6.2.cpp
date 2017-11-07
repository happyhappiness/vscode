static short pgp_mic_from_packet (unsigned char *p, size_t len)
{
  /* is signature? */
  if ((p[0] & 0x3f) != PT_SIG)
  {
    dprint (1, (debugfile, "pgp_mic_from_packet: tag = %d, want %d.\n",
		p[0]&0x3f, PT_SIG));
    return -1;
  }
  
  if (len >= 18 && p[1] == 3)
    /* version 3 signature */
    return (short) p[17];
  else if (len >= 5 && p[1] == 4)
    /* version 4 signature */
    return (short) p[4];
  else
  {
    dprint (1, (debugfile, "pgp_mic_from_packet: Bad signature packet.\n"));
    return -1;
  }
}