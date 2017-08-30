    }

  }



  cmd = aprintf( "%s%s%s",

                 data->set.str[STRING_CUSTOMREQUEST]?

                 data->set.str[STRING_CUSTOMREQUEST]:

                 (data->set.ftp_list_only?"NLST":"LIST"),

                 lstArg? " ": "",

                 lstArg? lstArg: "" );



  if(!cmd) {

    free(lstArg);

