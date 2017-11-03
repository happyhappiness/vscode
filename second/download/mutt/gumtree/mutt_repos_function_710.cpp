static void show_one_sig_validity (gpgme_ctx_t ctx, int idx, STATE *s)
{
  gpgme_verify_result_t result = NULL;
  gpgme_signature_t sig = NULL;
  const char *txt = NULL;

  result = gpgme_op_verify_result (ctx);
  if (result)
    for (sig = result->signatures; sig && (idx > 0); sig = sig->next, idx--);

  switch (sig ? sig->validity : 0)
      {
      case GPGME_VALIDITY_UNKNOWN:
	txt = _("WARNING: We have NO indication whether "
		"the key belongs to the person named "
		"as shown above\n");
	break;
      case GPGME_VALIDITY_UNDEFINED:
	break;
      case GPGME_VALIDITY_NEVER:
	txt = _("WARNING: The key does NOT BELONG to "
		"the person named as shown above\n");
	break;
      case GPGME_VALIDITY_MARGINAL:
	txt = _("WARNING: It is NOT certain that the key "
		"belongs to the person named as shown above\n");
	break;
      case GPGME_VALIDITY_FULL:
      case GPGME_VALIDITY_ULTIMATE:
	txt = NULL;
	break;
      }
  if (txt)
    state_attach_puts (txt, s);
}