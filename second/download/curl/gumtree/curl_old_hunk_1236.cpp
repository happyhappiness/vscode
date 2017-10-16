             newline here */
          fputs("\n", progressbar.out);

        if(config->writeout)
          ourWriteOut(curl, &outs, config->writeout);

        if(config->writeenv)
          ourWriteEnv(curl);

        /*
        ** Code within this loop may jump directly here to label 'show_error'
        ** in order to display an error message for CURLcode stored in 'res'
        ** variable and exit loop once that necessary writing and cleanup
        ** in label 'quit_urls' has been done.
        */
