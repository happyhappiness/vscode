        if (checklist->keepMatching())
            checklist->markFinished(answer, "AuthenticateAcl exception");
        return -1; // other
    }
}

wordlist *
ACLMaxUserIP::dump() const
{
    if (!maximum)
        return NULL;

    wordlist *W = NULL;

    char buf[128];

    snprintf(buf, sizeof(buf), "%lu", (unsigned long int) maximum);

    wordlistAdd(&W, buf);

    return W;
}
