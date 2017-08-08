{
		archive_set_error(a, -1,
		    "PROGRAMMER ERROR: Function '%s' invoked"
		    " on '%s' archive object, which is not supported.",
		    function,
		    handle_type);
		a->state = ARCHIVE_STATE_FATAL;
		return (ARCHIVE_FATAL);
	}