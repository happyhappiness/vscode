		ret = check_symref(argv[0], quiet, shorten, 1);
		break;
	case 2:
		if (!strcmp(argv[0], "HEAD") &&
		    !starts_with(argv[1], "refs/"))
			die("Refusing to point HEAD outside of refs/");
		ret = !!create_symref(argv[0], argv[1], msg);
		break;
	default:
		usage_with_options(git_symbolic_ref_usage, options);
	}
	return ret;
}
