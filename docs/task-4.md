# Responding with 404

In this stage, your program will need to extract the path from the HTTP request.

Here's what the contents of a HTTP request look like:
```
GET /index.html HTTP/1.1
Host: localhost:4221
User-Agent: curl/7.64.1
```
- `GET /index.html HTTP/1.1` is the [start line](https://developer.mozilla.org/en-US/docs/Web/HTTP/Messages#start_line)
    - `GET` is the HTTP Method
    - `/index` is the path
    - `HTTP/1.1` is the HTTP Version
- `Host: localhost:4221` and `User-Agent: curl/7.64.1` are HTTP headers.
- Note that all of these lines are separated by `\r\n`, not just `\n`.

In this stage, we'll only focus on extracting the path from the request.

If the path is `/`, you'll need to respond with a 200 OK response. Otherwise, you'll need to respond with a 404 Not Found response.
