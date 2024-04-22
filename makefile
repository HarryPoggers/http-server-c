build: server parser
	@echo "Linking..."
	@gcc build/server.o build/httpparser.o -o build/http-server

server:
	@set -e
	@echo "Compiling main Server..."
	@gcc -c -o build/server.o app/server.c

parser:
	@echo "Compiling parser..."
	@gcc -c -o build/httpparser.o app/httpparser.c
