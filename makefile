build: server parser stringutil response filehandler
	@echo "Linking..."
	@gcc build/*.o -o build/http-server -s -pthread
server:
	@set -e
	@echo "Compiling main Server..."
	@gcc -c -o build/server.o app/server.c -g -pthread

parser:
	@echo "Compiling parser..."
	@gcc -c -o build/httpparser.o app/httpparser.c -g

stringutil:
	@echo "Compiling stringutil..."
	@gcc -c -o build/stringutil.o app/stringutil.c -g

response:
	@echo "Compiling response..."
	@gcc -c -o build/response.o app/httpresponse.c -g

filehandler:
	@echo "Compiling filehandler..."
	@gcc -c -o build/filehandler.o app/filehandler.c -g

debug: server parser stringutil response filehandler
	@echo "Compiling with debug symbols..."
	@gcc build/*.o -o build/http-server -g -pthread
