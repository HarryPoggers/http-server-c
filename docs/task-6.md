# Parse headers

In this stage, your program will need to parse HTTP request headers.

The tester will send you a request of the form GET `/user-agent`, and it'll include a `User-Agent` header.

Your program will need to respond with a `200 OK` response. The response should have a content type of `text/plain`, and it should contain the user agent value as the body.

For example, here's a request you might receive:
```
GET /user-agent HTTP/1.1
Host: localhost:4221
User-Agent: curl/7.64.1
```

and here's the response you're expected to send back:
```
HTTP/1.1 200 OK
Content-Type: text/plain
Content-Length: 11

curl/7.64.1
```
