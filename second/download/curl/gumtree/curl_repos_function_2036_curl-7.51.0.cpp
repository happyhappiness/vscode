void Curl_sasl_init(struct SASL *sasl, const struct SASLproto *params)
{
  sasl->params = params;           /* Set protocol dependent parameters */
  sasl->state = SASL_STOP;         /* Not yet running */
  sasl->authmechs = SASL_AUTH_NONE; /* No known authentication mechanism yet */
  sasl->prefmech = SASL_AUTH_DEFAULT; /* Prefer all mechanisms */
  sasl->authused = SASL_AUTH_NONE; /* No the authentication mechanism used */
  sasl->resetprefs = TRUE;         /* Reset prefmech upon AUTH parsing. */
  sasl->mutual_auth = FALSE;       /* No mutual authentication (GSSAPI only) */
  sasl->force_ir = FALSE;          /* Respect external option */
}