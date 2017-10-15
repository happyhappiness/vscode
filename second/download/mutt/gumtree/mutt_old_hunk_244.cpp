	    break;
	}

	snprintf (buff, sizeof (buff), _("%s Do you really want to use the key?"),
		  _(s));

	if (mutt_yesorno (buff, M_NO) != M_YES)
	{
	  mutt_clear_error ();
	  break;
	}
      }

