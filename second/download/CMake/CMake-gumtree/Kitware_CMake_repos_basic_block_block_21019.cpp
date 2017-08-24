{
    uv_sem_wait(&barrier->turnstile1);
    uv_sem_post(&barrier->turnstile2);
  }