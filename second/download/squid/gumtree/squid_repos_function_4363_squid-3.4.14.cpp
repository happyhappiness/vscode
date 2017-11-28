Ssl::ErrorDetailsManager &Ssl::ErrorDetailsManager::GetInstance()
{
    if (!TheDetailsManager)
        TheDetailsManager = new Ssl::ErrorDetailsManager;

    assert(TheDetailsManager);
    return *TheDetailsManager;
}