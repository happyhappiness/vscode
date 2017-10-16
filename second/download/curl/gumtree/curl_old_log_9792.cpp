fputs(
"              should  not  replace internally set headers without knowing per-\n"
"              fectly well what you're doing. Remove an internal header by giv-\n"
"              ing  a  replacement  without  content  on  the right side of the\n"
"              colon, as in: -H \"Host:\". If you send the custom header with no-\n"
"              value  then its header must be terminated with a semicolon, such\n"
"              as -H \"X-Custom-Header;\" to send \"X-Custom-Header:\".\n"
"\n"
, stdout);