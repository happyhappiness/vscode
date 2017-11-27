static int notify_email_shutdown (void)
{
  pthread_mutex_lock (&session_lock);

  if (session != NULL)
    smtp_destroy_session (session);
  session = NULL;

  if (authctx != NULL)
    auth_destroy_context (authctx);
  authctx = NULL;

  auth_client_exit();

  pthread_mutex_unlock (&session_lock);
  return (0);
}