(n) {
      case 1:
        return test1(argc, argv);
      case 2:
        return test2(argc, argv);
      case 3:
        return test3(argc, argv);
      case 4:
        return test4(argc, argv);
      case 5:
        return test5(argc, argv);
      case 6:
        test6(argc, argv);
        return 0;
      case 7:
        return test7(argc, argv);
      case 8:
        return test8(argc, argv);
      case 9:
        return test9(argc, argv);
      case 10:
        return test10(argc, argv);
      case 108:
        return test8_grandchild(argc, argv);
      case 109:
        return test9_grandchild(argc, argv);
      case 110:
        return test10_grandchild(argc, argv);
    }