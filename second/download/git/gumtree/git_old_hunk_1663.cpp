				break;
			}
			if (constcmp(t + strlen("Node-"), "kind"))
				continue;
			strbuf_addf(&rev_ctx.note, "%s\n", t);
			if (!strcmp(val, "dir"))
				node_ctx.type = REPO_MODE_DIR;
			else if (!strcmp(val, "file"))
				node_ctx.type = REPO_MODE_BLB;
			else
				fprintf(stderr, "Unknown node-kind: %s\n", val);
			break;
		case sizeof("Node-action"):
			if (constcmp(t, "Node-action"))
				continue;
