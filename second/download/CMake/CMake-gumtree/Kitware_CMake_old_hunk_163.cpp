		}
		offset += datasize;
	}
#ifdef DEBUG
	if (offset != extra_length)
	{
		fprintf(stderr,
		    "Extra data field contents do not match reported size!\n");
	}
#endif
}

/*
