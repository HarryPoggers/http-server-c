server:
	@set -e
	@gcc -lcurl app/server.c -o build/server.o

run: server
	@gcc build/server.o -o build/http-server
