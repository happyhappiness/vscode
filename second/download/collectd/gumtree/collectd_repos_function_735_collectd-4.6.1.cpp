static int notify_email_shutdown (void)
{
  smtp_destroy_session (session);
  auth_destroy_context (authctx);
  auth_client_exit();
  return (0);
}