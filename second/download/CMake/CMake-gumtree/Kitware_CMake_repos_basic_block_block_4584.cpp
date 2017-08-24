{
        /* we have the precision specified from a parameter, so we make that
           parameter's info setup properly */
        long k = precision - 1;
        vto[i].precision = k;
        vto[k].type = FORMAT_WIDTH;
        vto[k].flags = FLAGS_NEW;
        /* can't use width or precision of width! */
        vto[k].width = 0;
        vto[k].precision = 0;
      }