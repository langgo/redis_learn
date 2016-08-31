FD_ZERO


```c
fcntl(fd, F_GETFL)
fcntl(fd, F_SETFL, flags | O_NONBLOCK)
setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes))
setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &buffsize, sizeof(buffsize)
setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof(yes))
inet_aton(host, &sa.sin_addr)
gethostbyname(host)
inet_ntoa(sa.sin_addr)
socket(AF_INET, SOCK_STREAM, 0)
htons(port)
connect(s, (struct sockaddr*)&sa, sizeof(sa))
setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)
htonl(INADDR_ANY)
bind(s, (struct sockaddr*)&sa, sizeof(sa))
listen(s, 5)
ntohs(sa.sin_port)
```