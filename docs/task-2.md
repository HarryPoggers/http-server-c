# Bind to a Port

In this stage, you'll create a TCP server that listens on port 4221.

TCP is the underlying protocol used by HTTP servers.

Tests
The tester will execute your program like this:
```bash
$ ./your_server.sh
```
Then, the tester will try to connect to your server on port 4221. The connection must succeed for you to pass this stage.
