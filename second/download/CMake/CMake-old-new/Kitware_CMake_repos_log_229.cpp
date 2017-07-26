archive_set_error(a, -1,
			    "INTERNAL ERROR: Function '%s' invoked with"
			    " archive structure in state '%s',"
			    " should be in state '%s'",
			    function,
			    write_all_states(states1, a->state),
			    write_all_states(states2, state));