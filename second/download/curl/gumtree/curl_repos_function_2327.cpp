static void entropy_init_mutex(entropy_context *ctx)
{
  /* lock 0 = entropy_init_mutex() */
  polarsslthreadlock_lock_function(0);
  if(entropy_init_initialized == 0) {
    entropy_init(ctx);
    entropy_init_initialized = 1;
  }
  polarsslthreadlock_unlock_function(0);
}