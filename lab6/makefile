default: lab6

lab6: server.c client.c
	gcc server.c -o server
	gcc client.c -o client

server: server.c
	gcc server.c -o server

client: client.c
	gcc client.c -o client

clean:
	-rm -f server
	-rm -f client