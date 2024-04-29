# Post a file

In this stage, your server will need to accept the contents of a file in a POST request and save it to a directory.

Just like in the previous stage, the tester will execute your program with a `--directory` flag like this:

```
./your_server.sh --directory <directory>
```

It'll then send you a request of the form `POST /files/<filename>`. The request body will contain the contents of the file.

You'll need to fetch the contents of the file from the request body and save it to `<directory>/<filename>`. The response code returned should be 201.

We pass in absolute path to your program using the `--directory` flag.
