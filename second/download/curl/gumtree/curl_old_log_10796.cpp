fputs(
"              colon, as in: -H \"Host:\". If you send the custom header with no-\n"
"              value  then its header must be terminated with a semicolon, such\n"
"              as -H \"X-Custom-Header;\" to send \"X-Custom-Header:\".\n"
"\n"
"              curl will make sure that each header  you  add/replace  is  sent\n"
"              with the proper end-of-line marker, you should thus not add that\n"
"              as a part of the header content: do not add newlines or carriage\n"
, stdout);