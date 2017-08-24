{
      schannel_cred.dwFlags |= SCH_CRED_NO_SERVERNAME_CHECK;
      infof(data, "schannel: verifyhost setting prevents Schannel from "
            "comparing the supplied target name with the subject "
            "names in server certificates.\n");
    }