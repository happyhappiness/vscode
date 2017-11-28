static void parse_ftp_epsv(acl_access **ftp_epsv)
{
    allow_t ftpEpsvDeprecatedAction;
    bool ftpEpsvIsDeprecatedRule = false;

    char *t = ConfigParser::PeekAtToken();
    if (!t) {
        self_destruct();
        return;
    }

    if (!strcmp(t, "off")) {
        (void)ConfigParser::NextToken();
        ftpEpsvIsDeprecatedRule = true;
        ftpEpsvDeprecatedAction = allow_t(ACCESS_DENIED);
    } else if (!strcmp(t, "on")) {
        (void)ConfigParser::NextToken();
        ftpEpsvIsDeprecatedRule = true;
        ftpEpsvDeprecatedAction = allow_t(ACCESS_ALLOWED);
    }

    // Check for mixing "ftp_epsv on|off" and "ftp_epsv allow|deny .." rules:
    //   1) if this line is "ftp_epsv allow|deny ..." and already exist rules of "ftp_epsv on|off"
    //   2) if this line is "ftp_epsv on|off" and already exist rules of "ftp_epsv allow|deny ..."
    // then abort
    if ((!ftpEpsvIsDeprecatedRule && FtpEspvDeprecated) ||
            (ftpEpsvIsDeprecatedRule && !FtpEspvDeprecated && *ftp_epsv != NULL)) {
        debugs(3, DBG_CRITICAL, "FATAL: do not mix \"ftp_epsv on|off\" cfg lines with \"ftp_epsv allow|deny ...\" cfg lines. Update your ftp_epsv rules.");
        self_destruct();
    }

    if (ftpEpsvIsDeprecatedRule) {
        // overwrite previous ftp_epsv lines
        delete *ftp_epsv;
        if (ftpEpsvDeprecatedAction == allow_t(ACCESS_DENIED)) {
            Acl::AndNode *ftpEpsvRule = new Acl::AndNode;
            ftpEpsvRule->context("(ftp_epsv rule)", config_input_line);
            ACL *a = ACL::FindByName("all");
            if (!a) {
                self_destruct();
                return;
            }
            ftpEpsvRule->add(a);
            *ftp_epsv = new Acl::Tree;
            (*ftp_epsv)->context("(ftp_epsv rules)", config_input_line);
            (*ftp_epsv)->add(ftpEpsvRule, ftpEpsvDeprecatedAction);
        } else
            *ftp_epsv = NULL;
        FtpEspvDeprecated = true;
    } else {
        aclParseAccessLine(cfg_directive, LegacyParser, ftp_epsv);
    }
}