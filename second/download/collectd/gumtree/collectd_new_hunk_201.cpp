		}
	} while (0);

	return (0);
} /* int us_open_socket */

static void *us_handle_client (void *arg)
{
	int fd;
	FILE *fhin, *fhout;
	char buffer[1024];
	char *fields[128];
