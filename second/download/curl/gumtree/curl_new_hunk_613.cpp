      /* use <eth0> or <192.168.10.10> style addresses. Anything except
	 this will make us try to get the "default" address.
	 NOTE: this is a changed behaviour since the released 4.1!
	 */
      GetStr(&config->ftpport, nextarg);
      break;
    case 'p':
      /* proxy tunnel for non-http protocols */
      config->proxytunnel ^= TRUE;
      break;

    case 'q': /* if used first, already taken care of, we do it like
		 this so we don't cause an error! */
      break;
    case 'Q':
      /* QUOTE command to send to FTP server */
      if(nextarg[0] == '-') {
