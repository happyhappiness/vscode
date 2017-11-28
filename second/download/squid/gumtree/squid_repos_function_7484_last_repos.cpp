void
Security::ServerOptions::parse(const char *token)
{
    if (!*token) {
        // config says just "ssl" or "tls" (or "tls-")
        encryptTransport = true;
        return;
    }

    // parse the server-only options
    if (strncmp(token, "dh=", 3) == 0) {
        // clear any previous Diffi-Helman configuration
        dh.clear();
        dhParamsFile.clear();
        eecdhCurve.clear();

        dh.append(token + 3);

        if (!dh.isEmpty()) {
            auto pos = dh.find(':');
            if (pos != SBuf::npos) {  // tls-dh=eecdhCurve:dhParamsFile
                eecdhCurve = dh.substr(0,pos);
                dhParamsFile = dh.substr(pos+1);
            } else {  // tls-dh=dhParamsFile
                dhParamsFile = dh;
                // empty eecdhCurve means "do not use EECDH"
            }
        }

        loadDhParams();

    } else if (strncmp(token, "dhparams=", 9) == 0) {
        if (!eecdhCurve.isEmpty()) {
            debugs(83, DBG_PARSE_NOTE(1), "UPGRADE WARNING: EECDH settings in tls-dh= override dhparams=");
            return;
        }

        // backward compatibility for dhparams= configuration
        dh.clear();
        dh.append(token + 9);
        dhParamsFile = dh;

        loadDhParams();

    } else {
        // parse generic TLS options
        Security::PeerOptions::parse(token);
    }
}