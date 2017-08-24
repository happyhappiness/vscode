f(port == 0 || port == 80)
    oauth = aprintf("user=%s\1host=%s\1auth=Bearer %s\1\1", user, host,
                    bearer)