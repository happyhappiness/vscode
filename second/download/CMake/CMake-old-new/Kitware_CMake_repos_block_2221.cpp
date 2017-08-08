{
  printf("foo: %d bar: %d foobar: %d barbar: %d baz: %d\n", foo(), bar(),
         foobar(), barbar(), baz());

  printf("tree_prefix_foo: %d tree_prefix_bar: %d tree_bar: %d tree_foobar: "
         "%d tree_baz: %d\n",
         tree_prefix_foo(), tree_prefix_bar(), tree_bar(), tree_foobar(),
         tree_baz());
  return 0;
}