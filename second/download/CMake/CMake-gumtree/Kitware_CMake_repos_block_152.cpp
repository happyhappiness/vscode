oauth = aprintf("user=%s\1host=%s\1port=%ld\1auth=Bearer %s\1\1", user,
                    host, port, bearer)