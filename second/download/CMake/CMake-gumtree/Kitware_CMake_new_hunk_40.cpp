					} else {

						fsobj_error(a_eno, a_estr,

						    errno,

						    "Could not stat ", path);

						res = (ARCHIVE_FAILED);

						break;

					}

