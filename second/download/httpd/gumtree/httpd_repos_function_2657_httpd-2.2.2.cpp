static void crypt_mutex_lock(void)
{
    pthread_mutex_lock(&crypt_mutex);
}