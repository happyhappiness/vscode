	    mutt_perror (tempfile);
	    mutt_sleep (5);
	    unlink (tempfile);
	    goto bail; 
	  }
	  break;
	case M_KENDRA:
	  if(fputs(KENDRA_SEP, fp) == EOF)
	  {
	    mutt_perror (tempfile);
	    mutt_sleep (5);
	    unlink (tempfile);
	    goto bail;
	  }
	  break;
	default:
	  if(fputs("\n", fp) == EOF) 
	  {
	    mutt_perror (tempfile);
	    mutt_sleep (5);
	    unlink (tempfile);
