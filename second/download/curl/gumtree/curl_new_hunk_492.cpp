             newline here */
          fputs("\n", progressbar.out);

        if(config->writeout)
          ourWriteOut(curl, config->writeout);
#ifdef USE_ENVIRONMENT
        if(config->writeenv)
          ourWriteEnv(curl);
#endif

        show_error:

#ifdef __VMS
        if(is_vms_shell()) {
          /* VMS DCL shell behavior */
          if(!config->showerror) {
            vms_show = VMSSTS_HIDE;
