	    break;
	}

	snprintf (buff, sizeof (buff), _("%s Do you really want to use the key?"),
		  _(s));

	if (mutt_yesorno (buff, 0) != 1)
	{
	  mutt_clear_error ();
	  break;
	}
      }

