
	case 'o':
	  if (getuid() == 0) {
	    preserve_uid=1;
	  } else {
	    fprintf(stderr,"-o only allowed for root\n");
	    exit(1);
	  }
	  break;

	case 'g':
	  preserve_gid=1;
	  break;

	case 'D':
	  if (getuid() == 0) {
	    preserve_devices=1;
	  } else {
	    fprintf(stderr,"-D only allowed for root\n");
	    exit(1);
	  }
	  break;

	case 't':
	  preserve_times=1;
	  break;
