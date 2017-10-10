					printf("~%d", name->generation);
			}
			printf("] ");
		}
		else
			printf("[%s] ",
			       find_unique_abbrev(commit->object.sha1,
						  DEFAULT_ABBREV));
	}
	puts(pretty_str);
	strbuf_release(&pretty);
}

