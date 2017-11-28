void
Auth::Ntlm::Config::init(Auth::Config *)
{
    if (authenticateProgram) {

        authntlm_initialised = 1;

        if (ntlmauthenticators == NULL)
            ntlmauthenticators = new statefulhelper("ntlmauthenticator");

        if (!proxy_auth_cache)
            proxy_auth_cache = hash_create((HASHCMP *) strcmp, 7921, hash_string);

        assert(proxy_auth_cache);

        ntlmauthenticators->cmdline = authenticateProgram;

        ntlmauthenticators->childs.updateLimits(authenticateChildren);

        ntlmauthenticators->ipc_type = IPC_STREAM;

        helperStatefulOpenServers(ntlmauthenticators);
    }
}