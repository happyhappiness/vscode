{
			if (e[0] == '0')
				t->async_io = 0;
			else
				t->async_io = 1;
			fprintf(stderr, "LIBARCHIVE_ASYNC_IO=%s\n",
			    (t->async_io)?"Enabled":"Disabled");
		}