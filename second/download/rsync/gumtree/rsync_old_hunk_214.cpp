
	case 'p':
	  preserve_perms=1;
	  break;

	case 'o':
	  if (getuid() == 0) {
	    preserve_uid=1;
	  } else {
	    fprintf(FERROR,"-o only allowed for root\n");
	    exit_cleanup(1);
	  }
	  break;

	case 'g':
	  preserve_gid=1;
	  break;

	case 'D':
	  if (getuid() == 0) {
	    preserve_devices=1;
	  } else {
	    fprintf(FERROR,"-D only allowed for root\n");
	    exit_cleanup(1);
	  }
	  break;

	case 't':
	  preserve_times=1;
	  break;

