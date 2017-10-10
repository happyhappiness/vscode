		fprintf(stderr,
			"If this is correct simply add it to the index "
			"for example\n"
			"by using:\n\n"
			"  git update-index --cacheinfo 160000 %s \"%s\"\n\n"
			"which will accept this suggestion.\n",
			oid_to_hex(&merges.objects[0].item->oid), path);
		break;

	default:
		MERGE_WARNING(path, "multiple merges found");
		for (i = 0; i < merges.nr; i++)
			print_commit((struct commit *) merges.objects[i].item);
