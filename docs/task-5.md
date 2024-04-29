# Respond with Content

In this stage, your program will need to respond with a body. In the previous stages we were only sending a status code, no body.

The task here is to parse the path from the HTTP request. We will send a random string in the url path you will need to parse that string and then respond with the parsed string (only) in the response body.

The tester will send you a request of the form `GET /echo/<a-random-string>`.

Your program will need to respond with a 200 OK response. The response should have a content type of `text/plain`, and it should contain the random string as the body.

As an example, here's a request you might receive:
```
GET /echo/abc HTTP/1.1
Host: localhost:4221
User-Agent: curl/7.64.1
```

And here's the response you're expected to send back:
```
HTTP/1.1 200 OK
Content-Type: text/plain
Content-Length: 3

abc
```

Remember, lines in the response are separated by `\r\n`, not just `\n`.
