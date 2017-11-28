void Ssl::ErrorDetailsManager::Shutdown()
{
    delete TheDetailsManager;
    TheDetailsManager = NULL;
}