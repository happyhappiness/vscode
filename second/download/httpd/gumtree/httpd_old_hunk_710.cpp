        }
        if (i != SERVER_DEAD)
            total+=status_array[i];
    }
    printf ("Total Running:\t%d\tout of: \t%d\n", total, ap_threads_limit);
    printf ("Requests per interval:\t%d\n", reqs);
    printf ("Skipped selects:\t%d\n", skips);
    printf ("Would blocks:\t%d\n", wblock);
}

static void show_server_data()
{
    ap_listen_rec *lr;
    module **m;
