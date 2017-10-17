warnf(config->global, "You can only select one HTTP request method! "
        "You asked for both %s and %s.\n",
        reqname[req], reqname[*store]);