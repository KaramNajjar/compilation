all: a b

clean_a:
	rm -f a/lex.yy.c
	rm -f hw2a
a: clean_a
	flex -o a/lex.yy.c a/lexer.lex
	g++ -o hw2a a/*.cpp a/*.c

clean_b:
	rm -f hw2b
b: clean_b
	g++ -o hw2b b/*.cpp

