debug: src/criterion.c
	gcc -ggdb -Wall -Wextra -o criterion-debug src/criterion.c

indent: src/criterion.c
	indent src/criterion.c