archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "Undefined option: `%s%s%s%s%s%s'",
		    vp?"":"!", mp?mp:"", mp?":":"", op, vp?"=":"", vp?vp:"")