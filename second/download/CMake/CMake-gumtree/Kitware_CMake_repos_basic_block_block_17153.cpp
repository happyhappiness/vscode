{
			if (shar->outpos > 0)
				uuencode_line(a, shar, shar->outbuff,
				    shar->outpos);
			archive_strcat(&shar->work, "`\nend\n");
			archive_strcat(&shar->work, "SHAR_END\n");
		}