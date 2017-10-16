           progressbar.calls)
          /* if the custom progress bar has been displayed, we output a
             newline here */
          fputs("\n", progressbar.out);

        if(config->writeout)
          ourWriteOut(curl, &outs, config->writeout);

        if(config->writeenv)
          ourWriteEnv(curl);

        /*
        ** Code within this loop may jump directly here to label 'show_error'
