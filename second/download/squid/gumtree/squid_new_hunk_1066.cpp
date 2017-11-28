        }

        if (type == LFT_NONE) {
            fatalf("Can't parse configuration token: '%s'\n", def);
        }

        // when {arg} field is after the token (old external_acl_type token syntax)
        // but accept only if there was none before the token
        if (*cur == '{' && !data.string) {
            char *cp;
            ++cur;
            l = strcspn(cur, "}");
            cp = (char *)xmalloc(l + 1);
            xstrncpy(cp, cur, l + 1);
            data.string = cp;
            cur += l;

            if (*cur == '}')
                ++cur;
        }

        if (*cur == ' ') {
            space = true;
            ++cur;
        }
    }

