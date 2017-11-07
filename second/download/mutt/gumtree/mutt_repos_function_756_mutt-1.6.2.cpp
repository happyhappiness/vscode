static int mutt_sasl_cb_log (void* context, int priority, const char* message)
{
  dprint (priority, (debugfile, "SASL: %s\n", message));

  return SASL_OK;
}