# Respond with 200

In this stage, you'll respond to a HTTP request with a 200 OK response.

Your program will need to:

- Accept a TCP connection
- Read data from the connection (we'll get to parsing it in later stages)
- Respond with `HTTP/1.1 200 OK\r\n\r\n` (there are two `\r\n`s at the end)
    - `HTTP/1.1 200 OK` is the [HTTP Status Line](https://developer.mozilla.org/en-US/docs/Web/HTTP/Messages#status_line).
    - `\r\n`, also known as [CRLF](https://developer.mozilla.org/en-US/docs/Glossary/CRLF), is the end-of-line marker that HTTP uses.
    - The first `\r\n` signifies the end of the status line.
    - The second `\r\n` signifies the end of the response headers section (which is empty in this case).


It's okay to ignore the data received from the connection for now. We'll get to parsing it in later stages.

For more details on the structure of a HTTP response, view the [MDN docs](https://developer.mozilla.org/en-US/docs/Web/HTTP/Messages#http_responses).
