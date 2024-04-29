# Get a file

In this stage, your server will need to return the contents of a file.

The tester will execute your program with a `--directory` flag like this:
```
./your_server.sh --directory <directory>
```

It'll then send you a request of the form `GET /files/<filename>`.

If `<filename>` exists in `<directory>`, you'll need to respond with a 200 OK response. The response should have a content type of `application/octet-stream`, and it should contain the contents of the file as the body.

If the file doesn't exist, return a 404.

We pass in absolute path to your program using the `--directory` flag.
