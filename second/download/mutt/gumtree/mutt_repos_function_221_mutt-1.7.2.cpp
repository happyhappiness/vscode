void mutt_print_message (HEADER *h)
{

  if (quadoption (OPT_PRINT) && (!PrintCmd || !*PrintCmd))
  {
    mutt_message (_("No printing command has been defined."));
    return;
  }
  
  if (query_quadoption (OPT_PRINT,
			h ? _("Print message?") : _("Print tagged messages?"))
		  	!= MUTT_YES)
    return;

  if (_mutt_pipe_message (h, PrintCmd,
			  option (OPTPRINTDECODE),
			  1,
			  option (OPTPRINTSPLIT),
			  "\f") == 0)
    mutt_message (h ? _("Message printed") : _("Messages printed"));
  else
    mutt_message (h ? _("Message could not be printed") :
		  _("Messages could not be printed"));
}