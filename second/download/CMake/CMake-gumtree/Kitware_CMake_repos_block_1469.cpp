{
			if (e[0] == '0')
				t->direct_io = 0;
			else
				t->direct_io = 1;
			fprintf(stderr, "LIBARCHIVE_DIRECT_IO=%s\n",
				(t->direct_io)?"Enabled":"Disabled");
		}