
	case 'u':
	  update_only=1;
	  break;

	case 'l':
#if SUPPORT_LINKS
	  preserve_links=1;
#endif
	  break;

	case 'H':
#if SUPPORT_HARD_LINKS
	  preserve_hard_links=1;
#endif
	  break;

	case 'p':
	  preserve_perms=1;
	  break;
