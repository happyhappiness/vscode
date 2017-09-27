            return LDAP_NO_SUCH_ATTRIBUTE;
        }
    }
    return result;
}

static int uldap_cache_checkuserid(request_rec *r, util_ldap_connection_t *ldc,
                                   const char *url, const char *basedn,
                                   int scope, char **attrs, const char *filter,
                                   const char *bindpw, const char **binddn,
                                   const char ***retvals)
{
