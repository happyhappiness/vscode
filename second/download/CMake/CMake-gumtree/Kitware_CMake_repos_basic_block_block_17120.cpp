{
		archive_strcat(&shar->work, "#!/bin/sh\n");
		archive_strcat(&shar->work, "# This is a shell archive\n");
		shar->wrote_header = 1;
	}