int thread_setup(void)
{
  int i;

  mutex_buf = (MUTEX_TYPE *)malloc(CRYPTO_num_locks(  ) * sizeof(MUTEX_TYPE));
  if (!mutex_buf)
    return 0;
  for (i = 0;  i < CRYPTO_num_locks(  );  i++)
    MUTEX_SETUP(mutex_buf[i]);
  CRYPTO_set_id_callback(id_function);
  CRYPTO_set_locking_callback(locking_function);
  return 1;
}