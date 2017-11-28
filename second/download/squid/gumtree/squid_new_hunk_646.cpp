                fprintf(stderr, "digest_file_auth: ignoring invalid password for %s\n", user);
                continue;
            }
            u = static_cast<user_data*>(xcalloc(1, sizeof(*u)));
            if (realm) {
                int len = strlen(user) + strlen(realm) + 2;
                u->hash.key = xmalloc(len);
                snprintf(static_cast<char*>(u->hash.key), len, "%s:%s", user, realm);
            } else {
                u->hash.key = xstrdup(user);
            }
            if (ha1)
                u->ha1 = xstrdup(ha1);
