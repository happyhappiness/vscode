static REMAILER *mix_new_remailer (void)
{
  return safe_calloc (1, sizeof (REMAILER));
}