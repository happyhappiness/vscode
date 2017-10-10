	 * These helpers read back data from fast-import on their stdin, which could
	 * be mixed with import commands, otherwise.
	 */

	if (finish_command(&fastimport))
		die("Error while running fast-import");

	/*
	 * The fast-import stream of a remote helper that advertises
	 * the "refspec" capability writes to the refs named after the
	 * right hand side of the first refspec matching each ref we
	 * were fetching.
