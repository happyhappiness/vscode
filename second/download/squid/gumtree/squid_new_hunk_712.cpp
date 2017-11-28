        if (checklist->keepMatching())
            checklist->markFinished(answer, "AuthenticateAcl exception");
        return -1; // other
    }
}

SBufList
ACLMaxUserIP::dump() const
{
    SBufList sl;
    if (!maximum)
        return sl;
    SBuf s;
    s.Printf("%d", maximum);
    sl.push_back(s);
    return sl;
}

