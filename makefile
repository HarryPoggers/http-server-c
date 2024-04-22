build: server parser stringutil response
	@echo "Linking..."
	@gcc build/*.o -o build/http-server

server:
	@set -e
	@echo "Compiling main Server..."
	@gcc -c -o build/server.o app/server.c

parser:
	@echo "Compiling parser..."
	@gcc -c -o build/httpparser.o app/httpparser.c

stringutil:
	@echo "Compiling stringutil..."
	@gcc -c -o build/stringutil.o app/stringutil.c

response:
	@echo "Compiling response..."
	@gcc -c -o build/response.o app/httpresponse.c

debug: server parser stringutil response
	@echo "Compiling with debug symbols..."
	@gcc build/*.o -g -o build/http-server
