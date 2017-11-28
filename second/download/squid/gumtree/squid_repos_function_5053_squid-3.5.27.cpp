static bool
Ftp::SupportedCommand(const SBuf &name)
{
    static std::set<SBuf> BlackList;
    if (BlackList.empty()) {
        /* Add FTP commands that Squid cannot relay correctly. */

        // We probably do not support AUTH TLS.* and AUTH SSL,
        // but let's disclaim all AUTH support to KISS, for now.
        BlackList.insert(cmdAuth());
    }

    // we claim support for all commands that we do not know about
    return BlackList.find(name) == BlackList.end();
}