static void crypt_mutex_unlock(void)
{
    pthread_mutex_unlock(&crypt_mutex);
}