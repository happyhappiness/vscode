int smime_application_smime_handler (BODY *m, STATE *s)
{
  return smime_handle_entity (m, s, NULL) ? 0 : -1;
}