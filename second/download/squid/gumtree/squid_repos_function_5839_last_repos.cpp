bool
validate_user(char *username, char *password)
{
    for (domaincontrollers_t::iterator dc = domaincontrollers.begin(); dc != domaincontrollers.end(); ++dc) {
        //std::cerr << "testing against " << dc->server << std::endl;
        const int rv = Valid_User(username, password, dc->server.c_str(), NULL, dc->domain.c_str());
        //std::cerr << "check result: " << rv << std::endl;
        if (rv == NTV_NO_ERROR)
            return true;
    }
    return false;
}