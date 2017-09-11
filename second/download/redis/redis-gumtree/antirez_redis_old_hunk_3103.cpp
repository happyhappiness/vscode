            server.lastsave,
            server.bgrewritechildpid != -1);

        if (server.loading) {
            double perc;
            time_t eta, elapsed;
