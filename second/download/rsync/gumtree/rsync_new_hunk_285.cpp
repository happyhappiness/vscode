
	case 'u':
	  update_only=1;
	  break;

	case 'l':
	  preserve_links=1;
	  break;

	case 'L':
	  copy_links=1;
	  break;

	case 'W':
	  whole_file=1;
	  break;

	case 'H':
#if SUPPORT_HARD_LINKS
	  preserve_hard_links=1;
#else 
	  fprintf(FERROR,"ERROR: hard links not supported on this platform\n");
	  exit_cleanup(1);
#endif
	  break;

	case 'p':
	  preserve_perms=1;
	  break;
